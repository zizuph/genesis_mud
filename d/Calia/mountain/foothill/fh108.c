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

    add_exit(FOOTHILL+"fh97", "north");
    add_exit(FOOTHILL+"fh98", "northeast");
    add_exit(FOOTHILL+"fh109", "east");
    add_exit(FOOTHILL+"fh118", "southeast");
    add_exit(FOOTHILL+"fh117", "south");
    add_exit(FOOTHILL+"fh116", "southwest");
    add_exit(FOOTHILL+"fh107", "west");
    add_exit(FOOTHILL+"fh96", "northwest");
}
