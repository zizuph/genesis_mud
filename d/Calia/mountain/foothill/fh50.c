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
    make_the_room("\n", "west", 1, 1);

    add_exit(FOOTHILL+"fh42", "north");
    add_exit(FOOTHILL+"fh43", "northeast");
    add_exit(FOOTHILL+"fh51", "east");
    add_exit(FOOTHILL+"fh57", "southeast");
    add_exit(FOOTHILL+"fh56", "south");
    add_exit(FOOTHILL+"fh55", "southwest");
    add_exit(FOOTHILL+"fh49", "west");
    add_exit(FOOTHILL+"fh41", "northwest");
}
