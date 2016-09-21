#include <stdio.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>

int main(int argc, char* argv[]) {
    Gtk::Main app(argc, argv);
    Gtk::Window fenetre;
    Gtk::Main::run(fenetre);
    return 0;
}