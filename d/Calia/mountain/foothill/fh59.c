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
    make_the_room("\n", "east", 1, 1);

    add_exit(FOOTHILL+"fh53", "north");
    add_exit(FOOTHILL+"fh54", "northeast");
    add_exit(FOOTHILL+"fh60", "east");
    add_exit(FOOTHILL+"fh66", "southeast");
    add_exit(FOOTHILL+"fh65", "south");
    add_exit(FOOTHILL+"fh64", "southwest");
    add_exit(FOOTHILL+"fh58", "west");
    add_exit(FOOTHILL+"fh52", "northwest");
}
