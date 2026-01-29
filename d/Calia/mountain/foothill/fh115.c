/*
  A room in the foothills of Mount Kyrus
  This room may contain a powerful force of krougs, led by one of
  the elite, an axe-wielder.

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
    make_the_room("\n", "south", 2, 1);

    add_exit(FOOTHILL+"fh106", "north");
    add_exit(FOOTHILL+"fh107", "northeast");
    add_exit(FOOTHILL+"fh116", "east");
    add_exit(FOOTHILL+"fh114", "west");
    add_exit(FOOTHILL+"fh105", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_AXE);
        reset_room();
    }
    else
        enable_reset(0);
}