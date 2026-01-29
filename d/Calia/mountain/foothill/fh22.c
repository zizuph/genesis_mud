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
    make_the_room("To the west and south you see a road.\n", 
                  "northwest", 1, 1);

    add_item("road", "To the west and south is a road that runs by " +
                     "from northwest to southeast.\n");

    add_exit(FOOTHILL+"fh11", "north");
    add_exit(FOOTHILL+"fh12", "northeast");
    add_exit(FOOTHILL+"fh23", "east");
    add_exit(FOOTHILL+"fh34", "southwest");
    add_exit(FOOTHILL+"fh10", "northwest");
    add_exit(ROAD+"road10", "west");
    add_exit(ROAD+"road9", "south");

}
