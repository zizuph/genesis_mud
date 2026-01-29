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
    make_the_room("\n", "southeast", 1, 1);

    add_exit(FOOTHILL+"fh99", "north");
    add_exit(FOOTHILL+"fh100", "northeast");
    add_exit(FOOTHILL+"fh111", "east");
    add_exit(FOOTHILL+"fh120", "southeast");
    add_exit(FOOTHILL+"fh119", "south");
    add_exit(FOOTHILL+"fh118", "southwest");
    add_exit(FOOTHILL+"fh109", "west");
    add_exit(FOOTHILL+"fh98", "northwest");
}
