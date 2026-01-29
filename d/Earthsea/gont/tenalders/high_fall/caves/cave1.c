/*
 * coded by Amelia 7/26/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#include <stdproperties.h>
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

public void
create_earthsea_room()
{
    object door;

    set_short("Limestone cave");
    set_long("You are standing in a dark cave. On the " +
        "walls of the cave you see crude pictographs drawn in " +
        "red paint...or blood. This perhaps is the entrance to " +
        "some secret place of worship. Stalactites hang from the " +
        "ceiling and acidic solution drips from them into glazed puddles " +
        "on the floor. The atmosphere here makes the hair on " +
        "the back of your neck stand up.\n");
    add_item((({"crude pictographs", "pictographs", "paint",
        "red paint", "blood"})),
        "The pictographs seem to depict a scene of ancient ritual " +
        "or sacrifice at an altar.\n");
    add_item((({"stalactites", "acidic solution", "puddles",
        "glazed puddles", "floor"})),
        "Stalactites formed from calcite solution hang from " +
        "the ceiling like long teeth. Acid drops onto the floor, " +
        "creating slippery puddles.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_NCAVETUNNEL);
    add_prop(ROOM_I_INSIDE, 1);
    add_tell("Acid drips from the stalactites onto the floor.\n");
    add_tell("From the bowels of the cave you hear a strange noise!\n");
    reset_room();
    set_tell_time(30);
    add_exit("../cliff_top", "out");
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/crystal_out");
    door->move(this_object());
}
