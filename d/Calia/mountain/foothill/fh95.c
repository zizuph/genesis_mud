
/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 16/8/95

  Modified, Maniac, 13/2/96

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

void
create_room()
{
    make_the_room("\n", "south", 0, 1);

    add_exit(FOOTHILL+"fh96", "east");
    add_exit(FOOTHILL+"fh107", "southeast");
    add_exit(FOOTHILL+"fh106", "south");
    add_exit(FOOTHILL+"fh105", "southwest");
    add_exit(FOOTHILL+"fh94", "west");
    add_exit(FOOTHILL+"fh85", "northwest");
}

