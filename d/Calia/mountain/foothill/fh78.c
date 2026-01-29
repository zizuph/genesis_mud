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
    make_the_room("\n", "southeast", 1, 1);

    add_exit(FOOTHILL+"fh70", "north");
    add_exit(FOOTHILL+"fh71", "northeast");
    add_exit(FOOTHILL+"fh79", "east");
    add_exit(FOOTHILL+"fh89", "southeast");
    add_exit(FOOTHILL+"fh88", "south");
    add_exit(FOOTHILL+"fh87", "southwest");
    add_exit(FOOTHILL+"fh77", "west");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_tough(random(5));
        reset_room();
    }
    else
        enable_reset(0);
}