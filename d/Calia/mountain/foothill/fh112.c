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

    add_exit(FOOTHILL+"fh101", "north");
    add_exit(FOOTHILL+"fh102", "northeast");
    add_exit(FOOTHILL+"fh120", "southwest");
    add_exit(FOOTHILL+"fh111", "west");
    add_exit(FOOTHILL+"fh100", "northwest");
}
