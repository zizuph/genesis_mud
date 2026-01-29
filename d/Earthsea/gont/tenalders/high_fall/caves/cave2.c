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

    set_short("In a limestone cave");
    set_long("The cave narrows, becoming a small confined " +
        "space. The stalactites nearly meet with stalagmites from " +
        "below looking very much like teeth. If you have any sense " +
        "you will go back now, else there is a crawl space that " +
        "leads down further into the dark cave.\n");
    add_item((({"cave", "space"})),
        "The space here is very confined by the hard rock " +
        "walls and ceiling of the cave. The crawl space leads down.\n");
    add_item((({"stalagmites", "stalactites"})),
        "Formed from mineral deposits, the stalagmites and " +
        "stalactites nearly meet, looking like teeth in a vast " +
        "evil jaw. You wonder if you can pass unharmed.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_NCAVETUNNEL);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG, 1);
    add_tell("Acid drips from the stalactites onto the floor.\n");
    add_tell("From below you think you hear someone chanting " +
        "in a strangely hypnotic manner.\n");
    reset_room();
    set_tell_time(30);
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/crystal_in");
    door->move(this_object());
    add_exit("cave3", "down", 0, 2);
}
