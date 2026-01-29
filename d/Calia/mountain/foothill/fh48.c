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
    make_the_room("\n", "east", 2, 1);

    add_exit(FOOTHILL+"fh40", "north");
    add_exit(FOOTHILL+"fh54", "south");
    add_exit(FOOTHILL+"fh53", "southwest");
    add_exit(FOOTHILL+"fh47", "west");
    add_exit(FOOTHILL+"fh39", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_regular(random(5));
        reset_room();
    }
    else
        enable_reset(0);
}