/*
 * The actors club theatre stage
 */
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "actor.h"

public nomask void
create_room()
{
    set_short("A stage");
    set_long("  The stage is bare of any kind of props or equipment of any kind. But... that only gives you the more freedom of course! You have an excellent opportunity of showing off your thespian talents here and now. The stage is yours!\n  There's a door leading backstage to the north.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit("/d/Genesis/clubs/rpg/th_tiers", "east");
    add_exit("/d/Genesis/clubs/rpg/ac_club", "north");
}
