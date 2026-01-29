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
                  "opening up. To the northeast you see a road.\n", 
                   "northwest", 2, 1);

    add_item("road", "To the northeast is a road that runs by " +
                     "from northwest to southeast.\n");

    add_item("moorland", "The faded green moorlands stretch out a long " +
                         "way in the lands to the north.\n");

    add_exit(FOOTHILL+"fh20", "east");
    add_exit(FOOTHILL+"fh33", "southeast");
    add_exit(FOOTHILL+"fh32", "south");
    add_exit(FOOTHILL+"fh31", "southwest");
    add_exit(ROAD+"road11", "northeast");
    add_exit(ROAD+"m35", "north");
    add_exit(ROAD+"m34", "northwest"); 
    add_exit(ROAD+"m36", "west");
}
