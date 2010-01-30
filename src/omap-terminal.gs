[indent=4]

def widget_send_key(widget: Gtk.Widget, key_name: string, state: Gdk.ModifierType)
    var keymap = Gdk.Keymap.get_default()
    var keyval = Gdk.keyval_from_name(key_name)
    keys: array of Gdk.KeymapKey
    keymap.get_entries_for_keyval(keyval, out keys)
    e: Gdk.Event* = new Gdk.Event(Gdk.EventType.KEY_PRESS)
    ek: Gdk.EventKey* = (Gdk.EventKey*)e
    ek->window = widget.window
    ek->send_event = 1
    ek->time = Gdk.CURRENT_TIME
    ek->state = state
    ek->keyval = keyval
    ek->hardware_keycode = (uint16)keys[0].keycode
    ek->group = (uchar)keys[0].group
    e->put()

class TermWindow: Gtk.Window
    term: Vte.Terminal
    selection_clipboard: Gtk.Clipboard
    primary_clipboard: Gtk.Clipboard
    chooser_dialog: Gtk.FileChooserDialog
    cancellable: Cancellable

    const DELAY: int = 10

    const UI_DESC: string = """
    <ui>
        <menubar name='MenuBar'>
            <menu action='FileMenu'>
                 <menuitem action='Open'/>
                 <menuitem action='Disconnect'/>
                <separator/>
                <menuitem action='Quit'/>
            </menu>
            <menu action='EditMenu'>
                 <menuitem action='Copy'/>
                <menuitem action='Paste'/>
                <menuitem action='Stop'/>
            </menu>
        </menubar>
        <toolbar name='ToolBar'>
            <toolitem action='Open'/>
            <toolitem action='Disconnect'/>
            <toolitem action='Copy'/>
            <toolitem action='Paste'/>
            <toolitem action='Stop'/>
            <separator name='Separator'/> 
            <toolitem action='Quit'/>
        </toolbar>
    </ui>
    """

    const entries: array of Gtk.ActionEntry = {
        {"FileMenu", null, "_File"},
        {"EditMenu", null, "_Edit"},
        {"Open", Gtk.STOCK_OPEN,
         "_Open", "<shift><control>O", "Open file", on_open},
        {"Disconnect", Gtk.STOCK_DISCONNECT,
         "_Disconnect", "<shift><control>X", "Disconnect", on_disconnect},
        {"Copy", Gtk.STOCK_COPY,
         "_Copy", "<shift><control>C", "Copy", on_copy},
        {"Paste", Gtk.STOCK_PASTE,
         "_Paste", "<shift><control>V", "Paste", on_paste},
        {"Stop", Gtk.STOCK_STOP,
         "_Stop", "<shift><control>S", "Stop", on_stop},
        {"Quit", Gtk.STOCK_QUIT,
         "_Quit", "<shift><control>Q", "Quit", on_quit}
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

        var separator = manager.get_widget("/ToolBar/Separator") as Gtk.SeparatorToolItem
        separator.set_expand(true)
        separator.set_draw(false)

        term = new Vte.Terminal()
        box.pack_start(term, true, true, 0)
        term.fork_command(null, null, null, null, true, true, true)
        term.child_exited += on_term_child_exited
        term.button_press_event += on_button_pressed
        
        selection_clipboard = Gtk.Clipboard.get(Gdk.SELECTION_CLIPBOARD)
        primary_clipboard = Gtk.Clipboard.get(Gdk.SELECTION_PRIMARY)
        
        box.show_all()
        term.grab_focus()

    def on_term_child_exited()
        destroy()

    def on_button_pressed(e: Gdk.EventButton): bool
        case e.button
            when 2
                primary_clipboard.request_text(on_clipboard_text)
                return true
            default
                return false

    def on_quit()
        Gtk.main_quit()

    def on_disconnect()
        widget_send_key(term, "X", Gdk.ModifierType.CONTROL_MASK)
        widget_send_key(term, "C", Gdk.ModifierType.CONTROL_MASK)
    
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
        selection_clipboard.request_text(on_clipboard_text)

    def on_clipboard_text(clipboard: Gtk.Clipboard, text: string)
        insert_text_with_fixed_delay(text)

    def insert_text_with_fixed_delay(text: string)
        if cancellable != null
            return
        cancellable = new Cancellable()
        insert_text_with_delay(text, DELAY)

    def on_stop()
        if cancellable != null
            cancellable.cancel()

    def async insert_text_with_delay(text: string, delay: uint)
        if cancellable == null
            return
        callback: SourceFunc = insert_text_with_delay.callback
        c: unichar
        iter: unowned string = text
        while (c=iter.get_char()) != 0 and not cancellable.is_cancelled()
            var str_builder = new StringBuilder()
            str_builder.append_unichar(c)
            term.feed_child(str_builder.str, -1)
            Timeout.add(delay, callback)
            yield
            iter = iter.next_char()
        cancellable = null

init
    Gtk.init(ref args)
    var window = new TermWindow()
    window.show()
    Gtk.main()
