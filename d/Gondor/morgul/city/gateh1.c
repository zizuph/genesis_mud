#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void   reset_room();

object *guards = allocate(6 + random(3));

public void
create_morgul_room()
{
    set_extraline("This is the room where the guards on duty at the "
      + "Morgul Gate spend their time. You can see a few beds in a "
      + "corner, and on the walls there are fixtures to hold weapons "
      + "and armour.");
    set_road(9);
    set_short_desc("in a guard room at the Morgul Gate");
    set_side("west");

    add_exit(MORGUL_DIR + "city/i_ngate","east","@@check_exit",1);
    add_prop(ROOM_I_INSIDE,1);
    add_gatehouse();
    reset_room();
}

public void
reset_room()
{
    set_alarm(0.0, 0.0, &clone_npcs(guards, MORGUL_DIR + "npc/ithil_guard", 1.0));
}

object *query_guards() { return guards; }

public void
reset_room_and_improve_guards(int level)
{
    guards += allocate(level);
    reset_room();
}

