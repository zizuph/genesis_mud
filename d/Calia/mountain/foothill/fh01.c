/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 20/7/95

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

void
create_room()
{
    make_the_room("To the west, northwest and north you see moorland " +
                  "opening up. To the southwest you see a road.\n", 
                  "northwest", 2, 1);

    add_item("road", "To the southwest is a road that runs by " +
                     "from northwest to southeast.\n");

    add_item("moorland", "The faded green moorlands stretch out a long " +
                         "way in the lands to the north.\n");

    add_exit(FOOTHILL+"fh02", "east");
    add_exit(FOOTHILL+"fh11", "southeast");
    add_exit(FOOTHILL+"fh10", "south");
    add_exit(ROAD+"road11", "southwest");
    add_exit(ROAD+"m28", "north");
    add_exit(ROAD+"m27", "northwest");
    add_exit(ROAD+"m32", "west");
}
