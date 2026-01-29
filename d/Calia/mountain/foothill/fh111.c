/*
  A room in the foothills of Mount Kyrus
  This room may contain a powerful force of krougs, led by one of
  the elite, a two-handed sword wielder.

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
    make_the_room("\n", "southeast", 2, 1);

    add_exit(FOOTHILL+"fh100", "north");
    add_exit(FOOTHILL+"fh101", "northeast");
    add_exit(FOOTHILL+"fh112", "east");
    add_exit(FOOTHILL+"fh120", "south");
    add_exit(FOOTHILL+"fh119", "southwest");
    add_exit(FOOTHILL+"fh110", "west");
    add_exit(FOOTHILL+"fh99", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_elite(random(6), ELITE_SPEAR);
        reset_room();
    }
    else
        enable_reset(0);
}