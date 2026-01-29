inherit "/std/object";
#include "/d/Kalad/defs.h";
/* Sarr */

void
create_object()
{
    set_name("table");
    set_adj("stone");
    add_adj("large");
    set_short("large stone table");
    set_long("This is a large table made of black stone. On it, you see "+
    "a few papers, maps, a book, daggers, pens, and some other strange "+
    "gadgets. The large goblin is sitting behind it. Many other chairs "+
    "surround it.\n");
    add_item("maps","They look like maps of Kabal.\n");
    add_item("papers","Written in strange goblin scrabble.\n");
    add_item("book","A large black book. Perhaps you should read it?\n");
    add_item("daggers","A few daggers lay scattered about the table.\n");
    add_item("pens","feather pens, and a few ink bottles.\n");
    add_prop(OBJ_M_NO_GET,"You don't want to do that.\n");
}

