inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("A small study room");
    INSIDE;
    set_long("You are now in a small study. There are candles "+
      "on the walls, and a small window also lets light in on the "+
      "south wall. There are book shelves, a desk and a couple of "+
      "chairs here.\n");
    add_item("candles","They burn softly, giving light and smell.\n");
    add_item("walls","They are very polished, and gleam with an "+
      "inner beauty.\n");
    add_item("window","Through this small window of clear glass you can "+
      "see directly out into the gardens. Before you is a strange scene...\n"+
      "The gardner is digging in the ground using a hoe with an odd "+
      "nervous look in his face, and in his hand, you see something "+
      "shining bright blue.\n");
    add_item("chairs","They are made of oak and are polished. They "+
      "have soft, velvet cushions on them.\n");
    add_item("desk","A large desk with papers, pens, books, etc on "+
      "it.\n");
    add_item("shelves","They contain many leather-bound books.\n");
    add_exit(NOBLE(aemilius/m1),"north",0,-1,-1);
}

