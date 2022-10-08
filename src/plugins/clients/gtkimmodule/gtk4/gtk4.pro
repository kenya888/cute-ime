TEMPLATE = lib
TARGET = im-cuteime

isEmpty(GTK4_IM_MODULE_DIR) {
    target.path = $$system(pkg-config --variable=libdir gtk4)/gtk-4.0/$$system(pkg-config --variable=gtk_binary_version gtk4)/immodules/
} else {
    target.path = $$GTK4_IM_MODULE_DIR
}

CONFIG += gtk
CONFIG -= qt
QT -= core gui

include(../../../../../cuteimeplugin.pri)

CONFIG += link_pkgconfig
PKGCONFIG += gtk4

HEADERS = \
    ../cuteimeimcontext.h \
    ../gtk2qt.h
SOURCES = \
    im-cuteime.c \
    cuteimeimcontext.c

DESTDIR = $$CUTEIME_BUILD_TREE/$$CUTEIME_LIBRARY_PATH/plugins/inputmethods/gtk4immodules

update_local_gtk_immodules.path = $$DESTDIR
update_local_gtk_immodules.depends = all
update_local_gtk_immodules.files = gtk.immodules

QMAKE_EXTRA_TARGETS += update_local_gtk_immodules

update_gtk_immodules.path = /etc/gtk-4.0
update_gtk_immodules.depends = install_target
update_gtk_immodules.files = gtk.immodules

INSTALLS += update_gtk_immodules

OTHER_FILES += \
    ../gtk2qtkey.tbl
