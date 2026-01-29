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
    make_the_room("To the northwest you see moorland opening up. To " +
                  "the west and south you see a road.\n", 
                   "northwest", 2, 1);

    add_item("road", "To the west and south is a road that runs by " +
                     "from northwest to southeast.\n");

    add_item("moorland", "The faded green moorlands stretch out a long " +
                         "way in the lands to the north.\n");

    add_exit(FOOTHILL+"fh01", "north");
    add_exit(FOOTHILL+"fh02", "northeast");
    add_exit(FOOTHILL+"fh11", "east");
    add_exit(FOOTHILL+"fh22", "southeast");
    add_exit(FOOTHILL+"fh20", "southwest");
    add_exit(ROAD+"road11", "west");
    add_exit(ROAD+"road10", "south");
    add_exit(ROAD+"m32", "northwest");

}
