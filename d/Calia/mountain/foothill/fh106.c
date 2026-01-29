/*
  A room in the foothills of Mount Kyrus
  This room may contain a medium force of krougs, consisting mostly of
  regulars.

  Coded by Maniac 20/7/95
  Modified, Maniac, 13/2/96

*/

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

inherit "/d/Calia/std/std_foothills";

void
create_room()
{
    make_the_room("\n", "south", 1, 1);

    add_exit(FOOTHILL+"fh95", "north");
    add_exit(FOOTHILL+"fh96", "northeast");
    add_exit(FOOTHILL+"fh107", "east");
    add_exit(FOOTHILL+"fh116", "southeast");
    add_exit(FOOTHILL+"fh115", "south");
    add_exit(FOOTHILL+"fh114", "southwest");
    add_exit(FOOTHILL+"fh105", "west");
    add_exit(FOOTHILL+"fh94", "northwest");
}
