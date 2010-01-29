[indent=4]

class TermWindow: Gtk.Window
    term: Vte.Terminal
    clipboard: Gtk.Clipboard
    chooser_dialog: Gtk.FileChooserDialog

    const UI_DESC: string = """
    <ui>
        <menubar name='MenuBar'>
            <menu action='FileMenu'>
                 <menuitem action='Open'/>
                <separator/>
                <menuitem action='Quit'/>
            </menu>
            <menu action='EditMenu'>
                 <menuitem action='Copy'/>
                <menuitem action='Paste'/>
            </menu>
        </menubar>
        <toolbar name='ToolBar'>
            <toolitem action='Open'/>
            <toolitem action='Copy'/>
            <toolitem action='Paste'/>
            <separator name='Separator' expand='true' draw='false'/> 
            <toolitem action='Quit'/>
        </toolbar>
    </ui>
    """

    const entries: array of Gtk.ActionEntry = {
        {"FileMenu", null, "_File"},
        {"EditMenu", null, "_Edit"},
        {"Open", Gtk.STOCK_OPEN,
         "_Open", "<control>O", "Open file", on_open},
        {"Copy", Gtk.STOCK_COPY,
         "_Copy", "<control><shift>C", "Copy", on_copy},
        {"Paste", Gtk.STOCK_PASTE,
         "_Paste", "<control><shift>V", "Paste", on_paste},
        {"Quit", Gtk.STOCK_QUIT,
         "_Quit", "<control>Q", "Quit", on_quit}
    }

    init
        var box = new Gtk.VBox(false, 0)
        add(box)
        title = "Omap Terminal"
        set_icon_name("terminal")
        destroy += on_quit

        var action_group = new Gtk.ActionGroup("Actions")
        action_group.add_actions(entries, this)

        var manager = new Gtk.UIManager()
        manager.insert_action_group(action_group, 0)
        add_accel_group(manager.get_accel_group())

        manager.add_ui_from_string(UI_DESC, -1)
        box.pack_start(manager.get_widget("/MenuBar"), false, false, 0)
        box.pack_start(manager.get_widget("/ToolBar"), false, false, 0)

        term = new Vte.Terminal()
        box.pack_start(term, true, true, 0)
        term.fork_command(null, null, null, null, true, true, true)
        term.child_exited += on_term_child_exited
        
        clipboard = Gtk.Clipboard.get(Gdk.SELECTION_CLIPBOARD)
        
        box.show_all()

    def on_term_child_exited()
        destroy()

    def on_quit()
        Gtk.main_quit()

    def on_open()
        if chooser_dialog == null
            chooser_dialog = new Gtk.FileChooserDialog(
                "Open file", this, Gtk.FileChooserAction.OPEN,
                Gtk.STOCK_CANCEL, Gtk.ResponseType.CANCEL,
                Gtk.STOCK_OPEN, Gtk.ResponseType.ACCEPT,
                null)
            chooser_dialog.destroy += on_chooser_dialog_destroy
        chooser_dialog.select_multiple = false
        chooser_dialog.response += on_chooser_response
        chooser_dialog.show()

    def on_chooser_response(response: int)
        case response
            when Gtk.ResponseType.ACCEPT
                var filename = chooser_dialog.get_filename()
                contents: string
                if FileUtils.get_contents(filename, out contents, null)
                    insert_text_with_fixed_delay(contents)
                chooser_dialog.destroy()
            when Gtk.ResponseType.CANCEL
                chooser_dialog.destroy()

    def on_chooser_dialog_destroy()
        chooser_dialog = null

    def on_copy()
        term.copy_clipboard()

    def on_paste()
        clipboard.request_text(on_clipboard_text)

    def on_clipboard_text(clipboard: Gtk.Clipboard, text: string)
        insert_text_with_fixed_delay(text)

    def insert_text_with_fixed_delay(text: string)
        insert_text_with_delay(text, 50)

    def async insert_text_with_delay(text: string, delay: uint)
        callback: SourceFunc = insert_text_with_delay.callback
        c: unichar
        iter: unowned string = text
        while (c=iter.get_char()) != 0
            var str_builder = new StringBuilder()
            str_builder.append_unichar(c)
            term.feed_child(str_builder.str, -1)
            Timeout.add(delay, callback)
            yield
            iter = iter.next_char()

init
    Gtk.init(ref args)
    var window = new TermWindow()
    window.show()
    Gtk.main()
