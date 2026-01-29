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
    make_the_room("To the north and east a road runs past.\n", 
                   "northwest", 1, 1);

    add_item("road", "You can see a road to the north and east. It runs " +
                     "northwest to southeast.\n");
    add_exit(FOOTHILL+"fh22", "northeast");
    add_exit(FOOTHILL+"fh44", "south");
    add_exit(FOOTHILL+"fh43", "southwest");
    add_exit(FOOTHILL+"fh33", "west");
    add_exit(FOOTHILL+"fh20", "northwest");
    add_exit(ROAD+"road9", "east");
    add_exit(ROAD+"road10", "north");
}
