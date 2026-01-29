// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In the bookroom of the High-Lord's castle");
    INSIDE;
    set_long("You have entered the lower half of what "+
      "appears to be the library of this castle. There "+
      "are bookshelves along the walls here with many different "+
      "colored books in them. There is a large rose-colored "+
      "table in the center of the room here, with many padded "+
      "chairs to sit on.\n");
    add_item("chairs","They are soft, velvet padded chairs.\n");
    add_item("table", "The large table holds a few scrolls, books "+
      "and quills.\n");
    add_item("bookshelves","They bookshelves are lined with many "+
      "books.\n");
    add_item("books","So many books to choose from. Most are about "+
      "history and politics though.\n");
    add_item("scrolls","A few scattered scrolls.\n");
    add_item("quills","They are used to write with.\n");
    add_item("carpet","The carpet is soft and warm.\n");
    add_item("torches","They hang on the walls.\n");

    add_exit(NOBLE + "castle/c30", "east", 0, 0);
    add_exit(NOBLE + "castle/c24", "north", 0, 0);
}
