#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *guards = allocate(3 + random(3));

public void
create_morgul_room()
{
    set_extraline("This is the room where the guards on duty at the "
      + "Mordor Gate spend their time. You can see a few beds in a "
      + "corner, and on the walls there are fixtures to hold weapons "
      + "and armour. A dark entrance at the back of the room leads "
      + "into another room.");
    set_road(9);
    set_short_desc("in a guard room at the Mordor Gate");
    set_side("east");

    add_exit(MORGUL_DIR + "city/i_egate","north","@@check_exit@@",1);
    add_exit(MORGUL_DIR + "city/eg_office","south","@@block_exit@@",1);
    add_prop(ROOM_I_INSIDE,1);
    add_gatehouse();
    reset_room();
}

public void
reset_room()
{
    set_alarm(1.0, 0.0, &clone_npcs(guards, MORGUL_DIR + "npc/ithil_guard", 4.0));
}
