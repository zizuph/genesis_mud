/*
  A room in the foothills of Mount Kyrus
  This room may contain a powerful force of krougs, led by one of
  the elite, a two-handed sword wielder.

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
    make_the_room("\n", "southeast", 2, 1);

    add_exit(FOOTHILL+"fh88", "north");
    add_exit(FOOTHILL+"fh89", "northeast");
    add_exit(FOOTHILL+"fh102", "east");
    add_exit(FOOTHILL+"fh112", "south");
    add_exit(FOOTHILL+"fh111", "southwest");
    add_exit(FOOTHILL+"fh100", "west");
    add_exit(FOOTHILL+"fh87", "northwest");
}
