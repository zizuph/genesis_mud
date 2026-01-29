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
    make_the_room("To the northwest you see moorland opening up.\n", 
                  "north", 2, 1);

    add_item("moorland", "The faded green moorlands stretch out a long " +
                         "way in the lands to the north.\n");

    add_exit(FOOTHILL+"fh03", "east");
    add_exit(FOOTHILL+"fh12", "southeast");
    add_exit(FOOTHILL+"fh11", "south");
    add_exit(FOOTHILL+"fh10", "southwest");
    add_exit(FOOTHILL+"fh01", "west");
    add_exit(ROAD+"m28", "northwest");
}
