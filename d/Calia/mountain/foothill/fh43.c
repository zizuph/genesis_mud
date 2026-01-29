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
    make_the_room("\n", "northwest", 1, 1);

    add_exit(FOOTHILL+"fh33", "north");
    add_exit(FOOTHILL+"fh34", "northeast");
    add_exit(FOOTHILL+"fh44", "east");
    add_exit(FOOTHILL+"fh51", "south");
    add_exit(FOOTHILL+"fh50", "southwest");
    add_exit(FOOTHILL+"fh42", "west");
    add_exit(FOOTHILL+"fh32", "northwest");
}
