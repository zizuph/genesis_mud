/*
  A room in the foothills of Mount Kyrus
  This room may contain a weak force of krougs, consisting mostly of
  the weakest krougs.


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
    make_the_room("\n", "south", 0, 1);


    add_exit(FOOTHILL+"fh97", "east");
    add_exit(FOOTHILL+"fh108", "southeast");
    add_exit(FOOTHILL+"fh107", "south");
    add_exit(FOOTHILL+"fh106", "southwest");
    add_exit(FOOTHILL+"fh95", "west");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_SPEAR);
        reset_room();
    }
    else
        enable_reset(0);
}

