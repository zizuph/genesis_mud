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
                  "northwest", 2, 1);

    add_item("moorland", "The faded green moorlands stretch out a long " +
                         "way in the lands to the north.\n");

    add_exit(FOOTHILL+"fh19", "north");
    add_exit(FOOTHILL+"fh20", "northeast");
    add_exit(FOOTHILL+"fh33", "east");
    add_exit(FOOTHILL+"fh43", "southeast");
    add_exit(FOOTHILL+"fh42", "south");
    add_exit(FOOTHILL+"fh41", "southwest");
    add_exit(FOOTHILL+"fh31", "west");
    add_exit(ROAD+"m36", "northwest");
}

