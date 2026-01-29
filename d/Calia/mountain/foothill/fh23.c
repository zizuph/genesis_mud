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
    make_the_room("To the southwest you see a road.\n", "north", 0, 1);

    add_item("road", "To the southwest is a road that runs by " +
                     "from northwest to southeast.\n");

    add_exit(ROAD+"road9", "southwest");
    add_exit(FOOTHILL+"fh12", "north");
    add_exit(FOOTHILL+"fh13", "northeast");
    add_exit(FOOTHILL+"fh24", "east");
    add_exit(FOOTHILL+"fh22", "west");
    add_exit(FOOTHILL+"fh11", "northwest");
}
