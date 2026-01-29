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
    make_the_room("\n", "west", 2, 1);

    add_exit(FOOTHILL+"fh49", "north");
    add_exit(FOOTHILL+"fh50", "northeast");
    add_exit(FOOTHILL+"fh56", "east");
    add_exit(FOOTHILL+"fh62", "southeast");
    add_exit(FOOTHILL+"fh61", "south");
}
