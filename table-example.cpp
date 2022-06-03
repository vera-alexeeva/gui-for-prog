#include <gtk/gtk.h>
#include <string>
#include <sstream>
#include "sorting.hpp"


GtkWidget *window;
GtkWidget *table_box;
GtkWidget *sorted_box;
GtkEntry *entry;

TMatr a;

void delete_table(GtkWidget *w) {
	GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(w));
    for(iter=children; iter!=NULL; iter=g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);
}

void fill_table(GtkWidget *table, int rows, int columns, TMatr a) {
    
    output_matrix(a);
    
    for (int i=0; i<rows; i++) {
        for (int k=0; k<columns; k++) {
            std::string text = "";
            text += std::to_string(a[i][k]);
            // write to gui
            GtkWidget *label0 = gtk_label_new(text.c_str());
            gtk_table_attach(GTK_TABLE(table), label0, k, k+1, i, i+1, GTK_FILL, GTK_FILL, 0, 0);
        }
    }
}

void create_table1(TMatr a, char *filename) {
	
    delete_table(table_box);
    delete_table(sorted_box);
	
	int rows = 2*n;
    int columns = 2*n;
	
	input_matrix(a, filename);
	
    GtkWidget *table = gtk_table_new(rows, columns, FALSE);
    gtk_table_set_col_spacings(GTK_TABLE(table), 20);
    fill_table(table, rows, columns, a);
	gtk_container_add(GTK_CONTAINER(table_box), table);
    
    gtk_widget_show_all(window);
}

void create_table2(TMatr a) {
	
    delete_table(table_box);
    delete_table(sorted_box);
	
	if(nCheck(n)){
		int rows = 2*n;
		int columns = 2*n;
		
		rand_input_matrix(a);
			
		GtkWidget *table = gtk_table_new(rows, columns, FALSE);
		gtk_table_set_col_spacings(GTK_TABLE(table), 20);
		fill_table(table, rows, columns, a);
		gtk_container_add(GTK_CONTAINER(table_box), table);
		
		gtk_widget_show_all(window);
	}
	else{
		
		GtkWidget *dialog;
        GtkWidget *label;
        GtkWidget *content_area;

        /* создать диалог */
        dialog = gtk_dialog_new_with_buttons("Ошибка",
                                             NULL,
                                             GTK_DIALOG_MODAL, // | GTK_DIALOG_DESTROY_WITH_PARENT,
                                             GTK_STOCK_OK,
                                             GTK_RESPONSE_ACCEPT,
                                             NULL);

        /* получить контейнер, в который будем пихать метку */
        content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

        /* сама метка */
        label = gtk_label_new("\n Некорректное значение n: \n 1 <= 2*N <= 1000 ");
        gtk_container_add(GTK_CONTAINER(content_area), label);
        gtk_widget_show(label);

        /* запускаем диалог */
        gtk_dialog_run(GTK_DIALOG(dialog));
        /* а потом прячем */
        gtk_widget_destroy(dialog);
		
		/*
		GtkMessageDialog errorDial ("1 <= 2*N <= RAZ",
									false,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_OK,
									true);
        //errorDial->set_title("Error !");
        gtk_dialog_run (GTK_DIALOG (errorDial));
        /*
        GtkWidget *dialog
        GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
		dialog = gtk_message_dialog_new (parent_window,
										 flags,
										 GTK_MESSAGE_ERROR,
										 GTK_BUTTONS_CLOSE,
										 "Error");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
		*/
		
	}
}

void create_sorted(TMatr a) {
	
	zerofication(a);
	sorting(a);
	
	int rows = 2*n;
    int columns = 2*n;
	
    GtkWidget *table = gtk_table_new(rows, columns, FALSE);
    gtk_table_set_col_spacings(GTK_TABLE(table), 20);
    fill_table(table, rows, columns, a);
	gtk_container_add(GTK_CONTAINER(sorted_box), table);
    
    gtk_widget_show_all(window);
}

void b1(GtkWidget *widget, gpointer data) {
	//....
	GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open File",
                                        GTK_WINDOW(gtk_widget_get_parent_window(GTK_WIDGET(widget))),
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                        GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                        NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        n = getNFromFile(filename);
		create_table1(a, filename);
        g_print(filename);
        g_free (filename);
    }
    gtk_widget_destroy (dialog);
	
}

void b2(GtkWidget *widget, gpointer data) {
	
	const char *value;
    value = gtk_entry_get_text (entry);
    stringstream strValue;
	strValue << value;
	strValue >> n;
    create_table2(a);
}

void b3(GtkWidget *widget, gpointer data) {
	create_sorted(a);
}

int main(int argc, char *argv[]) {
    
    GtkWidget *vbox;
    GtkWidget *bbox;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (window, 600, 400);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_title(GTK_WINDOW(window), "::Test GTK3 Table::");
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	bbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    table_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    sorted_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    
    entry = (GtkEntry*)gtk_entry_new();
    gtk_entry_set_text (entry, "4");
    
    GtkWidget *button1 = gtk_button_new_with_label("Table from file");
    gtk_widget_set_size_request(button1, 70, 30);
    gtk_widget_set_halign(button1, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button1, GTK_ALIGN_CENTER);

    GtkWidget *button2 = gtk_button_new_with_label("Random table");
    gtk_widget_set_size_request(button2, 70, 30);
    gtk_widget_set_halign(button2, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button2, GTK_ALIGN_CENTER);
    
    GtkWidget *button3 = gtk_button_new_with_label("Sort table");
    gtk_widget_set_size_request(button3, 70, 30);
    gtk_widget_set_halign(button3, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(button3, GTK_ALIGN_CENTER);


    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(b1), NULL);
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(b2), NULL);
    g_signal_connect(G_OBJECT(button3), "clicked", G_CALLBACK(b3), NULL);
	
    gtk_container_add(GTK_CONTAINER(bbox), button1);
    gtk_container_add(GTK_CONTAINER(bbox), GTK_WIDGET(entry));
    gtk_container_add(GTK_CONTAINER(bbox), button2);
    gtk_container_add(GTK_CONTAINER(bbox), button3);
    gtk_container_add(GTK_CONTAINER(vbox), bbox);
    gtk_container_add(GTK_CONTAINER(vbox), table_box);
    gtk_container_add(GTK_CONTAINER(vbox), sorted_box);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

