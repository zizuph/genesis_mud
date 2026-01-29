/*
  A room in the foothills of Mount Kyrus
  This room may contain a weak force of krougs, consisting mostly of
  the weakest krougs.

  Coded by Maniac 20/7/95

  Modified, Maniac, 13/2/96

*/
inherit "/d/Calia/std/std_foothills";

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"

void
create_room()
{
    make_the_room("\n", "east", 0, 1);

    add_exit(FOOTHILL+"fh52", "north");
    add_exit(FOOTHILL+"fh53", "northeast");
    add_exit(FOOTHILL+"fh59", "east");
    add_exit(FOOTHILL+"fh65", "southeast");
    add_exit(FOOTHILL+"fh64", "south");
}

