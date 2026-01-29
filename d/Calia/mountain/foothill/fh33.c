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
    make_the_room("To the northeast a road runs past.\n", 
                  "northwest", 1, 1);

    add_item("road", "To the northeast a road runs past. It runs " +
                     "northwest to southeast.\n");
    add_exit(FOOTHILL+"fh20", "north");
    add_exit(FOOTHILL+"fh34", "east");
    add_exit(FOOTHILL+"fh44", "southeast");
    add_exit(FOOTHILL+"fh43", "south");
    add_exit(FOOTHILL+"fh42", "southwest");
    add_exit(FOOTHILL+"fh32", "west");
    add_exit(FOOTHILL+"fh19", "northwest");
    add_exit(ROAD+"road10", "northeast");
}
