#include "../default.h"
inherit "/std/room";

void
create_room()
{
    set_short("The island");
    set_long("A barren, rocky wasteland. In all directions save for the "+
      "north, an endless waste stretches out of view. To your north a large "+
      "endless sea stretches far into the distant horizon. There is a small "+
      "pier here.\n");
    add_item(({"pier"}),
      "Nothing more than a collection of large stones piled on the beach.\n");
}

