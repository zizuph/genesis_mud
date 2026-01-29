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
    make_the_room("\n", "east", 2, 1);

    add_exit(FOOTHILL+"fh54", "north");
    add_exit(FOOTHILL+"fh66", "south");
    add_exit(FOOTHILL+"fh65", "southwest");
    add_exit(FOOTHILL+"fh59", "west");
    add_exit(FOOTHILL+"fh53", "northwest");
}
