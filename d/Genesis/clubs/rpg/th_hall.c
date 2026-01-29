/*
 * The actors club theatre hallway
 */
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "actor.h"

public nomask void
create_room()
{
    set_short("A hallway");
    set_long("  You're standing in a dimly lit hallway. The floor is covered with a red carpet stretching from the entrance to the theatre proper. A cubicle on the left, apparently intended for the purpose of selling tickets, has a sign on it.\n\n");

    add_item("cubicle", "An empty cubicle with a cardboard sign pasted to the desk.\n");
    add_item("sign", "Free admission!\n");
    add_cmd_item("sign", "read", "Free admission!\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    
    add_exit("/d/Genesis/clubs/rpg/theatre", "east");
    add_exit("/d/Genesis/clubs/rpg/th_tiers", "west");
}
