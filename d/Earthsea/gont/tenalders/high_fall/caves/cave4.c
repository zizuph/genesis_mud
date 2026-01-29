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
    set_short("Down in a limestone cave");
    set_long("The cave becomes a tunnel that twists and " +
        "turns. You have a suffocating feeling of claustrophobia " +
        "here. Strange noises seem to echo from somewhere deep " +
        "inside the mountain.\n");
    add_item((({"tunnel", "cave"})),
        "You feel like you are in the bowels of the earth, surrounded " +
        "by hard rock. The tunnel twists downward.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_NCAVETUNNEL);
    add_prop(ROOM_S_DARK_LONG, 1);
    add_tell("Moisture drips down the walls.\n");
    add_exit("cave3", "up", 0, 3);
    add_exit("cave5", "down", 0, 2);
    reset_room();
    set_tell_time(30);
}
