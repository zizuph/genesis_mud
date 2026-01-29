/*
  A room in the foothills of Mount Kyrus
  This room may contain a powerful force of krougs, led by one of
  the elite, a barbed spear wielder.

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
    make_the_room("\n", "east", 2, 1);

    add_exit(FOOTHILL+"fh66", "north");
    add_exit(FOOTHILL+"fh80", "south");
    add_exit(FOOTHILL+"fh79", "southwest");
    add_exit(FOOTHILL+"fh71", "west");
    add_exit(FOOTHILL+"fh65", "northwest");

    if (KROUG_BRAIN->reset_check(file_name(this_object()))) {
        set_num_tough(random(5));
        reset_room();
    }
    else
        enable_reset(0);
}