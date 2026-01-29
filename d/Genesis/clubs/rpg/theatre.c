/*
 * The actors club theatre
 */
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "actor.h"

public nomask void
create_room()
{
    set_short("A theatre");

    set_long("  You're standing on the lawn to what appears to be a theatre building. It's not very big, nor very impressive in architecture, yet there's something about it that suggests a feeling of grandeur.\n  The entrance to the theatre is right in front of you, the doors are open.\n\n");

    add_cmd_item(({"door", "doors"}), ({"close", "open"}), ({"The doors seem to be stuck in their open position.\n", "The doors are already open.\n"}));

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_exit("/d/Genesis/start/human/wild2/s_road3", "east");
    add_exit("/d/Genesis/clubs/rpg/th_hall", "west");
}





