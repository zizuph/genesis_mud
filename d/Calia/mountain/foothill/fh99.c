/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 15/8/95
  Modified, Maniac, 13/2/96

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

void
create_room()
{
    make_the_room("\n", "southeast", 1, 1);

    add_exit(FOOTHILL+"fh86", "north");
    add_exit(FOOTHILL+"fh87", "northeast");
    add_exit(FOOTHILL+"fh100", "east");
    add_exit(FOOTHILL+"fh111", "southeast");
    add_exit(FOOTHILL+"fh110", "south");
    add_exit(FOOTHILL+"fh109", "southwest");
    add_exit(FOOTHILL+"fh98", "west");
}
