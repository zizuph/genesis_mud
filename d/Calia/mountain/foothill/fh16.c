/*
  A room in the foothills of Mount Kyrus

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
    make_the_room("\n", "northeast", 1, 1);

    add_exit(FOOTHILL+"fh07", "north");
    add_exit(FOOTHILL+"fh08", "northeast");
    add_exit(FOOTHILL+"fh17", "east");
    add_exit(FOOTHILL+"fh28", "southeast");
    add_exit(FOOTHILL+"fh27", "south");
    add_exit(FOOTHILL+"fh26", "southwest");
    add_exit(FOOTHILL+"fh15", "west");
    add_exit(FOOTHILL+"fh06", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_regular(random(5));
        reset_room();
    }
    else
        enable_reset(0);
}