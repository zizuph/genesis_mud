/*
  A room in the foothills of Mount Kyrus
  This room may contain a medium force of krougs, consisting mostly of
  regulars.

  Coded by Maniac 20/7/95
  Modified, Maniac, 13/2/96

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
    make_the_room("\n", "south", 1, 1);

    add_exit(FOOTHILL+"fh98", "north");
    add_exit(FOOTHILL+"fh99", "northeast");
    add_exit(FOOTHILL+"fh110", "east");
    add_exit(FOOTHILL+"fh119", "southeast");
    add_exit(FOOTHILL+"fh118", "south");
    add_exit(FOOTHILL+"fh117", "southwest");
    add_exit(FOOTHILL+"fh108", "west");
    add_exit(FOOTHILL+"fh97", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_AXE);
        reset_room();
    }
    else
        enable_reset(0);
}