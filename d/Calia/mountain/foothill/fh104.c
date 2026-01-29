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
    make_the_room("\n", "southwest", 2, 1);

    add_exit(FOOTHILL+"fh93", "north");
    add_exit(FOOTHILL+"fh94", "northeast");
    add_exit(FOOTHILL+"fh105", "east");
    add_exit(FOOTHILL+"fh114", "southeast");
    add_exit(FOOTHILL+"fh113", "south");
    add_exit(FOOTHILL+"fh103", "west");
    add_exit(FOOTHILL+"fh92", "northwest");
}
