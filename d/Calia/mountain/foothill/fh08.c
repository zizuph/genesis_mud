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
    make_the_room("\n", "northeast", 2, 1);

    add_exit(FOOTHILL+"fh18", "southeast");
    add_exit(FOOTHILL+"fh17", "south");
    add_exit(FOOTHILL+"fh16", "southwest");
    add_exit(FOOTHILL+"fh07", "west");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_regular(random(5));
        reset_room();
    }
    else
        enable_reset(0);
}