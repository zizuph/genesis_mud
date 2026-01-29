/*
  A room in the foothills of Mount Kyrus

  Coded by Maniac 20/7/95

*/

inherit "/d/Calia/std/std_foothills";

#include <stdproperties.h>
#include <macros.h>
#include "foothill.h"
#include "/d/Calia/sys/kroug.h"
#include "kroug_reset.c"

void
create_room()
{
    make_the_room("\n", "southwest", 1, 1);

    add_exit(FOOTHILL+"fh76", "north");
    add_exit(FOOTHILL+"fh85", "east");
    add_exit(FOOTHILL+"fh94", "southeast");
    add_exit(FOOTHILL+"fh93", "south");
    add_exit(FOOTHILL+"fh92", "southwest");
    add_exit(FOOTHILL+"fh83", "west");
    add_exit(FOOTHILL+"fh75", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_tough(random(5));
        reset_room();
    }
    else
        enable_reset(0);
}