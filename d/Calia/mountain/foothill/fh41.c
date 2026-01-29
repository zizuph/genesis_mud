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

    add_exit(FOOTHILL+"fh31", "north");
    add_exit(FOOTHILL+"fh32", "northeast");
    add_exit(FOOTHILL+"fh42", "east");
    add_exit(FOOTHILL+"fh50", "southeast");
    add_exit(FOOTHILL+"fh49", "south");
}
