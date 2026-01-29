/*
  A room in the foothills of Mount Kyrus
  This room may contain a powerful force of krougs, led by one of
  the elite, an axe-wielder.

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
    make_the_room("\n", "south", 2, 1);

    add_exit(FOOTHILL+"fh105", "north");
    add_exit(FOOTHILL+"fh106", "northeast");
    add_exit(FOOTHILL+"fh115", "east");
    add_exit(FOOTHILL+"fh113", "west");
    add_exit(FOOTHILL+"fh104", "northwest");
}
