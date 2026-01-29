/*
  A room in the foothills of Mount Kyrus
  This room may contain a powerful force of krougs, led by a
  kroug commander.

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
    make_the_room("\n", "south", 2, 1);

    add_exit(FOOTHILL+"fh109", "north");
    add_exit(FOOTHILL+"fh110", "northeast");
    add_exit(FOOTHILL+"fh119", "east");
    add_exit(FOOTHILL+"fh117", "west");
    add_exit(FOOTHILL+"fh108", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_SWORD);
        reset_room();
    }
    else
        enable_reset(0);
}