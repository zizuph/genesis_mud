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
    make_the_room("\n", "southwest", 2, 1);

    add_exit(FOOTHILL+"fh83", "north");
    add_exit(FOOTHILL+"fh84", "northeast");
    add_exit(FOOTHILL+"fh93", "east");
    add_exit(FOOTHILL+"fh104", "southeast");
    add_exit(FOOTHILL+"fh103", "south");
    add_exit(FOOTHILL+"fh91", "west");
    add_exit(FOOTHILL+"fh82", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_SWORD);
        reset_room();
    }
    else
        enable_reset(0);
}