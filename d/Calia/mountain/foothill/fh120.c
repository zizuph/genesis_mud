/*
  A room in the foothills of Mount Kyrus
  This room may contain a powerful force of krougs, led by a
  very powerful kroug, a kroug commander with the sword of 
  darkness.

  Coded by Maniac 15/8/95

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
    make_the_room("\n", "southeast", 2, 1);

    add_exit(FOOTHILL+"fh111", "north");
    add_exit(FOOTHILL+"fh112", "northeast");
    add_exit(FOOTHILL+"fh119", "west");
    add_exit(FOOTHILL+"fh110", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_AXE);
        reset_room();
    }
    else
        enable_reset(0);
}