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
    make_the_room("To the northwest you see moorland opening up. To the " +
                  "north and east you see a road.\n", "northwest", 2, 1);

    add_item("road", "To the north and east is a road that runs by " +
                     "from northwest to southeast.\n");
    add_item("moorland", "The faded green moorlands stretch out a long " +
                         "way in the lands to the north.\n");
    add_exit(FOOTHILL+"fh10", "northeast");
    add_exit(FOOTHILL+"fh34", "southeast");
    add_exit(FOOTHILL+"fh33", "south");
    add_exit(FOOTHILL+"fh32", "southwest");
    add_exit(FOOTHILL+"fh19", "west");
    add_exit(ROAD+"road11", "north");
    add_exit(ROAD+"road10", "east");
    add_exit(ROAD+"m35", "northwest");
}

