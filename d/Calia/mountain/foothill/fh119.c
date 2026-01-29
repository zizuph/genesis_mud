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

    add_exit(FOOTHILL+"fh110", "north");
    add_exit(FOOTHILL+"fh111", "northeast");
    add_exit(FOOTHILL+"fh120", "east");
    add_exit(FOOTHILL+"fh118", "west");
    add_exit(FOOTHILL+"fh109", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_commanders(1);
        set_num_tough(random(2)+2);
        set_num_regular(random(2));
        reset_room();
    }
    else
        enable_reset(0);
}
