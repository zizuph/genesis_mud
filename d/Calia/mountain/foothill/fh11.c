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
    make_the_room("To the southwest you see a road.\n", "northwest", 1, 1);

    add_item("road", "To the southwest is a road that runs by " +
                     "from northwest to southeast.\n");

    add_exit(FOOTHILL+"fh02", "north");
    add_exit(FOOTHILL+"fh03", "northeast");
    add_exit(FOOTHILL+"fh12", "east");
    add_exit(FOOTHILL+"fh23", "southeast");
    add_exit(FOOTHILL+"fh22", "south");
    add_exit(ROAD+"road10", "southwest");
    add_exit(FOOTHILL+"fh10", "west");
    add_exit(FOOTHILL+"fh01", "northwest");

}
