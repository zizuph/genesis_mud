/*
  A room in the foothills of Mount Kyrus
  This room may contain a medium force of krougs, consisting mostly of
  regulars.

  Coded by Maniac 15/8/95
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

    add_exit(FOOTHILL+"fh96", "north");
    add_exit(FOOTHILL+"fh97", "northeast");
    add_exit(FOOTHILL+"fh108", "east");
    add_exit(FOOTHILL+"fh117", "southeast");
    add_exit(FOOTHILL+"fh116", "south");
    add_exit(FOOTHILL+"fh115", "southwest");
    add_exit(FOOTHILL+"fh106", "west");
    add_exit(FOOTHILL+"fh95", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_SWORD);
        reset_room();
    }
    else
        enable_reset(0);
}