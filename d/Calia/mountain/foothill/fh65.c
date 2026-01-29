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
    make_the_room("\n", "east", 1, 1);

    add_exit(FOOTHILL+"fh59", "north");
    add_exit(FOOTHILL+"fh60", "northeast");
    add_exit(FOOTHILL+"fh66", "east");
    add_exit(FOOTHILL+"fh72", "southeast");
    add_exit(FOOTHILL+"fh71", "south");
    add_exit(FOOTHILL+"fh70", "southwest");
    add_exit(FOOTHILL+"fh64", "west");
    add_exit(FOOTHILL+"fh58", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_tough(random(5));
        reset_room();
    }
    else
        enable_reset(0);
}