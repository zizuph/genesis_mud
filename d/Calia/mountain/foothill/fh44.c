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
    make_the_room("To the northeast you see a road that runs up " +
                  "to the mountain.\n", "northwest", 0, 1);

    add_item("road", "You can see a road that runs up to the mountain " +
                     "to the northeast.\n");
    add_exit(FOOTHILL+"fh34", "north");
    add_exit(FOOTHILL+"fh51", "southwest");
    add_exit(FOOTHILL+"fh43", "west");
    add_exit(FOOTHILL+"fh33", "northwest");
    add_exit(ROAD+"road9", "northeast");
}
