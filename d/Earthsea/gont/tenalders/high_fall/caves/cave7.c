/*
 * coded by Amelia 7/26/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <stdproperties.h>

public void
create_earthsea_room()
{
    set_short("Tunnel hallway.");
    set_long("The tunnel levels off here. Deep under the " +
        "earth, you feel the pressure of tons of solid rock above " +
        "and around you.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_NCAVETUNNEL);
    add_prop(ROOM_S_DARK_LONG, 1);
    add_tell("Moisture drips down the walls.\n");
    add_exit("cave6", "up", 0, 3);
    add_exit("tower_1", "northeast");
    reset_room();
    set_tell_time(30);
}
