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
    make_the_room("\n", "west", 0, 1);

    add_exit(FOOTHILL+"fh51", "north");
    add_exit(FOOTHILL+"fh63", "south");
    add_exit(FOOTHILL+"fh62", "southwest");
    add_exit(FOOTHILL+"fh56", "west");
    add_exit(FOOTHILL+"fh50", "northwest");
}
