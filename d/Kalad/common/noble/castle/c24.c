// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In the bookroom of the High-Lord's castle");
    INSIDE;
    set_long("You now stand in the north part of the bookroom "+
    "of this castle. Here, more bookshelves line the walls. In "+
    "the center here are many couches to sit on for reading.\n");
    add_item("couches","The couches are made of soft leather, and "+
    "look very comfortable to sit in.\n");    
    add_item("bookshelves","They bookshelves are lined with many "+
    "books.\n");
    add_item("books","So many books to choose from. Most are about "+
    "history and politics though.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c29", "south", 0, 0);
}
