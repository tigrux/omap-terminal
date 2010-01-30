/* omap-terminal.c generated by valac, the Vala compiler
 * generated from omap-terminal.gs, do not modify */


#include <glib.h>
#include <glib-object.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <vte/vte.h>
#include <gio/gio.h>
#include <glib/gstdio.h>


#define TYPE_TERM_WINDOW (term_window_get_type ())
#define TERM_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TERM_WINDOW, TermWindow))
#define TERM_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_TERM_WINDOW, TermWindowClass))
#define IS_TERM_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TERM_WINDOW))
#define IS_TERM_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_TERM_WINDOW))
#define TERM_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_TERM_WINDOW, TermWindowClass))

typedef struct _TermWindow TermWindow;
typedef struct _TermWindowClass TermWindowClass;
typedef struct _TermWindowPrivate TermWindowPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_string_free0(var) ((var == NULL) ? NULL : (var = (g_string_free (var, TRUE), NULL)))
typedef struct _TermWindowInsertTextWithDelayData TermWindowInsertTextWithDelayData;

struct _TermWindow {
	GtkWindow parent_instance;
	TermWindowPrivate * priv;
	VteTerminal* term;
	GtkClipboard* selection_clipboard;
	GtkClipboard* primary_clipboard;
	GtkFileChooserDialog* chooser_dialog;
	GCancellable* cancellable;
};

struct _TermWindowClass {
	GtkWindowClass parent_class;
};

struct _TermWindowInsertTextWithDelayData {
	int _state_;
	GAsyncResult* _res_;
	GSimpleAsyncResult* _async_result;
	TermWindow* self;
	char* text;
	guint delay;
	GSourceFunc callback;
	GSourceFunc _tmp0_;
	GDestroyNotify callback_target_destroy_notify;
	void* callback_target;
	gunichar c;
	const char* iter;
	gboolean _tmp1_;
	GString* str_builder;
	GCancellable* _tmp2_;
};


static gpointer term_window_parent_class = NULL;

void widget_put_accelerator (GtkWidget* widget, const char* accelerator);
GType term_window_get_type (void);
enum  {
	TERM_WINDOW_DUMMY_PROPERTY
};
#define TERM_WINDOW_DELAY 10
#define TERM_WINDOW_UI_DESC "\n    <ui>\n        <menubar name='MenuBar'>\n            <menu action='FileMenu'>\n                 <menuitem action='Open'/>\n                 <menuitem action='Disconnect'/>\n                <separator/>\n                <menuitem action='Quit'/>\n            </menu>\n            <menu action='EditMenu'>\n                 <menuitem action='Copy'/>\n                <menuitem action='Paste'/>\n                <menuitem action='Stop'/>\n            </menu>\n        </menubar>\n        <toolbar name='ToolBar'>\n            <toolitem action='Open'/>\n            <toolitem action='Disconnect'/>\n            <toolitem action='Copy'/>\n            <toolitem action='Paste'/>\n            <toolitem action='Stop'/>\n            <separator name='Separator'/> \n            <toolitem action='Quit'/>\n        </toolbar>\n    </ui>\n    "
void term_window_on_open (TermWindow* self);
static void _term_window_on_open_gtk_action_callback (GtkAction* action, gpointer self);
void term_window_on_disconnect (TermWindow* self);
static void _term_window_on_disconnect_gtk_action_callback (GtkAction* action, gpointer self);
void term_window_on_copy (TermWindow* self);
static void _term_window_on_copy_gtk_action_callback (GtkAction* action, gpointer self);
void term_window_on_paste (TermWindow* self);
static void _term_window_on_paste_gtk_action_callback (GtkAction* action, gpointer self);
void term_window_on_stop (TermWindow* self);
static void _term_window_on_stop_gtk_action_callback (GtkAction* action, gpointer self);
void term_window_on_quit (TermWindow* self);
static void _term_window_on_quit_gtk_action_callback (GtkAction* action, gpointer self);
void term_window_on_term_child_exited (TermWindow* self);
void term_window_on_clipboard_text (TermWindow* self, GtkClipboard* clipboard, const char* text);
static void _term_window_on_clipboard_text_gtk_clipboard_text_received_func (GtkClipboard* clipboard, const char* text, gpointer self);
gboolean term_window_on_button_pressed (TermWindow* self, GdkEventButton* e);
void term_window_on_chooser_dialog_destroy (TermWindow* self);
static void _term_window_on_chooser_dialog_destroy_gtk_object_destroy (GtkFileChooserDialog* _sender, gpointer self);
void term_window_on_chooser_response (TermWindow* self, gint response);
static void _term_window_on_chooser_response_gtk_dialog_response (GtkFileChooserDialog* _sender, gint response_id, gpointer self);
void term_window_insert_text_with_fixed_delay (TermWindow* self, const char* text);
void term_window_insert_text_with_delay (TermWindow* self, const char* text, guint delay, GAsyncReadyCallback _callback_, gpointer _user_data_);
void term_window_insert_text_with_delay_finish (TermWindow* self, GAsyncResult* _res_);
static void term_window_insert_text_with_delay_data_free (gpointer _data);
static void term_window_insert_text_with_delay_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_);
static gboolean _term_window_insert_text_with_delay_co_gsource_func (gpointer self);
static gboolean term_window_insert_text_with_delay_co (TermWindowInsertTextWithDelayData* data);
TermWindow* term_window_new (void);
TermWindow* term_window_construct (GType object_type);
static void _term_window_on_quit_gtk_object_destroy (TermWindow* _sender, gpointer self);
static void _term_window_on_term_child_exited_vte_terminal_child_exited (VteTerminal* _sender, gpointer self);
static gboolean _term_window_on_button_pressed_gtk_widget_button_press_event (VteTerminal* _sender, GdkEventButton* event, gpointer self);
static GObject * term_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties);
static void term_window_finalize (GObject* obj);
void _main (char** args, int args_length1);

static const GtkActionEntry TERM_WINDOW_entries[] = {{"FileMenu", NULL, "_File"}, {"EditMenu", NULL, "_Edit"}, {"Open", GTK_STOCK_OPEN, "_Open", "<shift><control>O", "Open file", (GCallback) _term_window_on_open_gtk_action_callback}, {"Disconnect", GTK_STOCK_DISCONNECT, "_Disconnect", "<shift><control>X", "Disconnect", (GCallback) _term_window_on_disconnect_gtk_action_callback}, {"Copy", GTK_STOCK_COPY, "_Copy", "<shift><control>C", "Copy", (GCallback) _term_window_on_copy_gtk_action_callback}, {"Paste", GTK_STOCK_PASTE, "_Paste", "<shift><control>V", "Paste", (GCallback) _term_window_on_paste_gtk_action_callback}, {"Stop", GTK_STOCK_STOP, "_Stop", "<shift><control>S", "Stop", (GCallback) _term_window_on_stop_gtk_action_callback}, {"Quit", GTK_STOCK_QUIT, "_Quit", "<shift><control>Q", "Quit", (GCallback) _term_window_on_quit_gtk_action_callback}};


void widget_put_accelerator (GtkWidget* widget, const char* accelerator) {
	guint keyval = 0U;
	GdkModifierType state = 0;
	GdkKeymap* keymap;
	gint keys_size;
	gint keys_length1;
	GdkKeymapKey* keys;
	GdkEvent* e;
	GdkEventKey* ek;
	g_return_if_fail (widget != NULL);
	g_return_if_fail (accelerator != NULL);
	gtk_accelerator_parse (accelerator, &keyval, &state);
	g_return_if_fail (keyval != 0);
	keymap = gdk_keymap_get_default ();
	keys = (keys_length1 = 0, NULL);
	gdk_keymap_get_entries_for_keyval (keymap, keyval, &keys, &keys_length1);
	e = gdk_event_new (GDK_KEY_PRESS);
	ek = (GdkEventKey*) e;
	(*ek).window = widget->window;
	(*ek).send_event = (gchar) 1;
	(*ek).time = (guint32) GDK_CURRENT_TIME;
	(*ek).state = state;
	(*ek).keyval = keyval;
	(*ek).hardware_keycode = (guint16) keys[0].keycode;
	(*ek).group = (guchar) keys[0].group;
	gdk_event_put (e);
	keys = (g_free (keys), NULL);
}


static void _term_window_on_open_gtk_action_callback (GtkAction* action, gpointer self) {
	term_window_on_open (self);
}


static void _term_window_on_disconnect_gtk_action_callback (GtkAction* action, gpointer self) {
	term_window_on_disconnect (self);
}


static void _term_window_on_copy_gtk_action_callback (GtkAction* action, gpointer self) {
	term_window_on_copy (self);
}


static void _term_window_on_paste_gtk_action_callback (GtkAction* action, gpointer self) {
	term_window_on_paste (self);
}


static void _term_window_on_stop_gtk_action_callback (GtkAction* action, gpointer self) {
	term_window_on_stop (self);
}


static void _term_window_on_quit_gtk_action_callback (GtkAction* action, gpointer self) {
	term_window_on_quit (self);
}


void term_window_on_term_child_exited (TermWindow* self) {
	g_return_if_fail (self != NULL);
	gtk_object_destroy ((GtkObject*) self);
}


static void _term_window_on_clipboard_text_gtk_clipboard_text_received_func (GtkClipboard* clipboard, const char* text, gpointer self) {
	term_window_on_clipboard_text (self, clipboard, text);
}


gboolean term_window_on_button_pressed (TermWindow* self, GdkEventButton* e) {
	gboolean result;
	g_return_val_if_fail (self != NULL, FALSE);
	switch ((*e).button) {
		case 2:
		{
			{
				gtk_clipboard_request_text (self->primary_clipboard, _term_window_on_clipboard_text_gtk_clipboard_text_received_func, self);
				result = TRUE;
				return result;
			}
			break;
		}
		default:
		{
			{
				result = FALSE;
				return result;
			}
			break;
		}
	}
}


void term_window_on_quit (TermWindow* self) {
	g_return_if_fail (self != NULL);
	gtk_main_quit ();
}


void term_window_on_disconnect (TermWindow* self) {
	g_return_if_fail (self != NULL);
	widget_put_accelerator ((GtkWidget*) self->term, "<control>A");
	widget_put_accelerator ((GtkWidget*) self->term, "<control>X");
}


static void _term_window_on_chooser_dialog_destroy_gtk_object_destroy (GtkFileChooserDialog* _sender, gpointer self) {
	term_window_on_chooser_dialog_destroy (self);
}


static void _term_window_on_chooser_response_gtk_dialog_response (GtkFileChooserDialog* _sender, gint response_id, gpointer self) {
	term_window_on_chooser_response (self, response_id);
}


void term_window_on_open (TermWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->chooser_dialog == NULL) {
		GtkFileChooserDialog* _tmp0_;
		self->chooser_dialog = (_tmp0_ = g_object_ref_sink ((GtkFileChooserDialog*) gtk_file_chooser_dialog_new ("Open file", (GtkWindow*) self, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL, NULL)), _g_object_unref0 (self->chooser_dialog), _tmp0_);
		g_signal_connect_object ((GtkObject*) self->chooser_dialog, "destroy", (GCallback) _term_window_on_chooser_dialog_destroy_gtk_object_destroy, self, 0);
	}
	gtk_file_chooser_set_select_multiple ((GtkFileChooser*) self->chooser_dialog, FALSE);
	g_signal_connect_object ((GtkDialog*) self->chooser_dialog, "response", (GCallback) _term_window_on_chooser_response_gtk_dialog_response, self, 0);
	gtk_widget_show ((GtkWidget*) self->chooser_dialog);
}


void term_window_on_chooser_response (TermWindow* self, gint response) {
	GError * _inner_error_;
	g_return_if_fail (self != NULL);
	_inner_error_ = NULL;
	switch (response) {
		case GTK_RESPONSE_ACCEPT:
		{
			{
				char* filename;
				char* contents;
				char* _tmp2_;
				gboolean _tmp1_;
				char* _tmp0_ = NULL;
				gboolean _tmp3_;
				filename = gtk_file_chooser_get_filename ((GtkFileChooser*) self->chooser_dialog);
				contents = NULL;
				_tmp3_ = (_tmp1_ = g_file_get_contents (filename, &_tmp0_, NULL, &_inner_error_), contents = (_tmp2_ = _tmp0_, _g_free0 (contents), _tmp2_), _tmp1_);
				if (_inner_error_ != NULL) {
					_g_free0 (filename);
					_g_free0 (contents);
					g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
					g_clear_error (&_inner_error_);
					return;
				}
				if (_tmp3_) {
					term_window_insert_text_with_fixed_delay (self, contents);
				}
				gtk_object_destroy ((GtkObject*) self->chooser_dialog);
				_g_free0 (filename);
				_g_free0 (contents);
			}
			break;
		}
		case GTK_RESPONSE_CANCEL:
		{
			{
				gtk_object_destroy ((GtkObject*) self->chooser_dialog);
			}
			break;
		}
	}
}


void term_window_on_chooser_dialog_destroy (TermWindow* self) {
	GtkFileChooserDialog* _tmp0_;
	g_return_if_fail (self != NULL);
	self->chooser_dialog = (_tmp0_ = NULL, _g_object_unref0 (self->chooser_dialog), _tmp0_);
}


void term_window_on_copy (TermWindow* self) {
	g_return_if_fail (self != NULL);
	vte_terminal_copy_clipboard (self->term);
}


void term_window_on_paste (TermWindow* self) {
	g_return_if_fail (self != NULL);
	gtk_clipboard_request_text (self->selection_clipboard, _term_window_on_clipboard_text_gtk_clipboard_text_received_func, self);
}


void term_window_on_clipboard_text (TermWindow* self, GtkClipboard* clipboard, const char* text) {
	g_return_if_fail (self != NULL);
	g_return_if_fail (clipboard != NULL);
	g_return_if_fail (text != NULL);
	term_window_insert_text_with_fixed_delay (self, text);
}


void term_window_insert_text_with_fixed_delay (TermWindow* self, const char* text) {
	GCancellable* _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (text != NULL);
	if (self->cancellable != NULL) {
		return;
	}
	self->cancellable = (_tmp0_ = g_cancellable_new (), _g_object_unref0 (self->cancellable), _tmp0_);
	term_window_insert_text_with_delay (self, text, (guint) TERM_WINDOW_DELAY, NULL, NULL);
}


void term_window_on_stop (TermWindow* self) {
	g_return_if_fail (self != NULL);
	if (self->cancellable != NULL) {
		g_cancellable_cancel (self->cancellable);
	}
}


static void term_window_insert_text_with_delay_data_free (gpointer _data) {
	TermWindowInsertTextWithDelayData* data;
	data = _data;
	_g_free0 (data->text);
	g_slice_free (TermWindowInsertTextWithDelayData, data);
}


void term_window_insert_text_with_delay (TermWindow* self, const char* text, guint delay, GAsyncReadyCallback _callback_, gpointer _user_data_) {
	TermWindowInsertTextWithDelayData* _data_;
	_data_ = g_slice_new0 (TermWindowInsertTextWithDelayData);
	_data_->_async_result = g_simple_async_result_new (G_OBJECT (self), _callback_, _user_data_, term_window_insert_text_with_delay);
	g_simple_async_result_set_op_res_gpointer (_data_->_async_result, _data_, term_window_insert_text_with_delay_data_free);
	_data_->self = self;
	_data_->text = g_strdup (text);
	_data_->delay = delay;
	term_window_insert_text_with_delay_co (_data_);
}


void term_window_insert_text_with_delay_finish (TermWindow* self, GAsyncResult* _res_) {
	TermWindowInsertTextWithDelayData* _data_;
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
}


static void term_window_insert_text_with_delay_ready (GObject* source_object, GAsyncResult* _res_, gpointer _user_data_) {
	TermWindowInsertTextWithDelayData* data;
	data = _user_data_;
	data->_res_ = _res_;
	term_window_insert_text_with_delay_co (data);
}


static gboolean _term_window_insert_text_with_delay_co_gsource_func (gpointer self) {
	return term_window_insert_text_with_delay_co (self);
}


static gboolean term_window_insert_text_with_delay_co (TermWindowInsertTextWithDelayData* data) {
	switch (data->_state_) {
		default:
		g_assert_not_reached ();
		case 0:
		{
			if (data->self->cancellable == NULL) {
				{
					if (data->_state_ == 0) {
						g_simple_async_result_complete_in_idle (data->_async_result);
					} else {
						g_simple_async_result_complete (data->_async_result);
					}
					g_object_unref (data->_async_result);
					return FALSE;
				}
			}
			data->callback_target_destroy_notify = NULL;
			data->callback_target = NULL;
			data->callback = (data->_tmp0_ = _term_window_insert_text_with_delay_co_gsource_func, data->callback_target = data, data->callback_target_destroy_notify = NULL, data->_tmp0_);
			data->iter = data->text;
			while (TRUE) {
				if ((data->c = g_utf8_get_char (data->iter)) != 0) {
					data->_tmp1_ = !g_cancellable_is_cancelled (data->self->cancellable);
				} else {
					data->_tmp1_ = FALSE;
				}
				if (!data->_tmp1_) {
					break;
				}
				data->str_builder = g_string_new ("");
				g_string_append_unichar (data->str_builder, data->c);
				vte_terminal_feed_child (data->self->term, data->str_builder->str, (glong) (-1));
				g_timeout_add_full (G_PRIORITY_DEFAULT, data->delay, data->callback, data->callback_target, data->callback_target_destroy_notify);
				data->_state_ = 1;
				return FALSE;
				case 1:
				;
				data->iter = g_utf8_next_char (data->iter);
				_g_string_free0 (data->str_builder);
			}
			data->self->cancellable = (data->_tmp2_ = NULL, _g_object_unref0 (data->self->cancellable), data->_tmp2_);
			(data->callback_target_destroy_notify == NULL) ? NULL : data->callback_target_destroy_notify (data->callback_target);
			data->callback = NULL;
			data->callback_target = NULL;
			data->callback_target_destroy_notify = NULL;
		}
		{
			if (data->_state_ == 0) {
				g_simple_async_result_complete_in_idle (data->_async_result);
			} else {
				g_simple_async_result_complete (data->_async_result);
			}
			g_object_unref (data->_async_result);
			return FALSE;
		}
	}
}


TermWindow* term_window_construct (GType object_type) {
	TermWindow * self;
	self = g_object_newv (object_type, 0, NULL);
	return self;
}


TermWindow* term_window_new (void) {
	return term_window_construct (TYPE_TERM_WINDOW);
}


static void _term_window_on_quit_gtk_object_destroy (TermWindow* _sender, gpointer self) {
	term_window_on_quit (self);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static void _term_window_on_term_child_exited_vte_terminal_child_exited (VteTerminal* _sender, gpointer self) {
	term_window_on_term_child_exited (self);
}


static gboolean _term_window_on_button_pressed_gtk_widget_button_press_event (VteTerminal* _sender, GdkEventButton* event, gpointer self) {
	return term_window_on_button_pressed (self, event);
}


static GObject * term_window_constructor (GType type, guint n_construct_properties, GObjectConstructParam * construct_properties) {
	GObject * obj;
	GObjectClass * parent_class;
	TermWindow * self;
	GError * _inner_error_;
	parent_class = G_OBJECT_CLASS (term_window_parent_class);
	obj = parent_class->constructor (type, n_construct_properties, construct_properties);
	self = TERM_WINDOW (obj);
	_inner_error_ = NULL;
	{
		GtkVBox* box;
		GtkActionGroup* action_group;
		GtkUIManager* manager;
		GtkWidget* _tmp0_;
		GtkSeparatorToolItem* separator;
		VteTerminal* _tmp1_;
		GtkClipboard* _tmp2_;
		GtkClipboard* _tmp3_;
		box = g_object_ref_sink ((GtkVBox*) gtk_vbox_new (FALSE, 0));
		gtk_container_add ((GtkContainer*) self, (GtkWidget*) box);
		gtk_window_set_title ((GtkWindow*) self, "Omap Terminal");
		gtk_window_set_icon_name ((GtkWindow*) self, "terminal");
		g_signal_connect_object ((GtkObject*) self, "destroy", (GCallback) _term_window_on_quit_gtk_object_destroy, self, 0);
		action_group = gtk_action_group_new ("Actions");
		gtk_action_group_add_actions (action_group, TERM_WINDOW_entries, G_N_ELEMENTS (TERM_WINDOW_entries), self);
		manager = gtk_ui_manager_new ();
		gtk_ui_manager_insert_action_group (manager, action_group, 0);
		gtk_window_add_accel_group ((GtkWindow*) self, gtk_ui_manager_get_accel_group (manager));
		gtk_ui_manager_add_ui_from_string (manager, TERM_WINDOW_UI_DESC, (gssize) (-1), &_inner_error_);
		if (_inner_error_ != NULL) {
			_g_object_unref0 (box);
			_g_object_unref0 (action_group);
			_g_object_unref0 (manager);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
		}
		gtk_box_pack_start ((GtkBox*) box, gtk_ui_manager_get_widget (manager, "/MenuBar"), FALSE, FALSE, (guint) 0);
		gtk_box_pack_start ((GtkBox*) box, gtk_ui_manager_get_widget (manager, "/ToolBar"), FALSE, FALSE, (guint) 0);
		separator = _g_object_ref0 ((_tmp0_ = gtk_ui_manager_get_widget (manager, "/ToolBar/Separator"), GTK_IS_SEPARATOR_TOOL_ITEM (_tmp0_) ? ((GtkSeparatorToolItem*) _tmp0_) : NULL));
		gtk_tool_item_set_expand ((GtkToolItem*) separator, TRUE);
		gtk_separator_tool_item_set_draw (separator, FALSE);
		self->term = (_tmp1_ = g_object_ref_sink ((VteTerminal*) vte_terminal_new ()), _g_object_unref0 (self->term), _tmp1_);
		gtk_box_pack_start ((GtkBox*) box, (GtkWidget*) self->term, TRUE, TRUE, (guint) 0);
		vte_terminal_fork_command (self->term, NULL, NULL, NULL, NULL, TRUE, TRUE, TRUE);
		g_signal_connect_object (self->term, "child-exited", (GCallback) _term_window_on_term_child_exited_vte_terminal_child_exited, self, 0);
		g_signal_connect_object ((GtkWidget*) self->term, "button-press-event", (GCallback) _term_window_on_button_pressed_gtk_widget_button_press_event, self, 0);
		self->selection_clipboard = (_tmp2_ = _g_object_ref0 (gtk_clipboard_get (GDK_SELECTION_CLIPBOARD)), _g_object_unref0 (self->selection_clipboard), _tmp2_);
		self->primary_clipboard = (_tmp3_ = _g_object_ref0 (gtk_clipboard_get (GDK_SELECTION_PRIMARY)), _g_object_unref0 (self->primary_clipboard), _tmp3_);
		gtk_widget_show_all ((GtkWidget*) box);
		gtk_widget_grab_focus ((GtkWidget*) self->term);
		_g_object_unref0 (box);
		_g_object_unref0 (action_group);
		_g_object_unref0 (manager);
		_g_object_unref0 (separator);
	}
	return obj;
}


static void term_window_class_init (TermWindowClass * klass) {
	term_window_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = term_window_constructor;
	G_OBJECT_CLASS (klass)->finalize = term_window_finalize;
}


static void term_window_instance_init (TermWindow * self) {
}


static void term_window_finalize (GObject* obj) {
	TermWindow * self;
	self = TERM_WINDOW (obj);
	_g_object_unref0 (self->term);
	_g_object_unref0 (self->selection_clipboard);
	_g_object_unref0 (self->primary_clipboard);
	_g_object_unref0 (self->chooser_dialog);
	_g_object_unref0 (self->cancellable);
	G_OBJECT_CLASS (term_window_parent_class)->finalize (obj);
}


GType term_window_get_type (void) {
	static GType term_window_type_id = 0;
	if (term_window_type_id == 0) {
		static const GTypeInfo g_define_type_info = { sizeof (TermWindowClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) term_window_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (TermWindow), 0, (GInstanceInitFunc) term_window_instance_init, NULL };
		term_window_type_id = g_type_register_static (GTK_TYPE_WINDOW, "TermWindow", &g_define_type_info, 0);
	}
	return term_window_type_id;
}


void _main (char** args, int args_length1) {
	TermWindow* window;
	gtk_init (&args_length1, &args);
	window = g_object_ref_sink (term_window_new ());
	gtk_widget_show ((GtkWidget*) window);
	gtk_main ();
	_g_object_unref0 (window);
}


int main (int argc, char ** argv) {
	g_type_init ();
	_main (argv, argc);
	return 0;
}




