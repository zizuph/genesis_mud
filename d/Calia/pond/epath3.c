/* This is a room in the elemental area northeast of the
frog pond in Calia. By Bishop, 5.2.99 */

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <pond.h>
#include <macros.h>

create_room()
{
    set_short("Near an area of tremors");

    set_long("You're standing in a fairly barren area. To your" +
        " north you see an area of tremors. The earth"+
        " groans and shifts, and a constant" +
        " rumble resonates through the area. Beyond that area," +
        " sheer mountains rise up, as they do to your east and" +
        " west. To your southeast lies a small hot pool at the" +
        " bottom of a cliff.\n");

    add_item(({"mountain", "mountains"}), "The sheer mountains" +
        " dominate the horizon in all directions except to the" +
        " south.\n");
    add_item(({"small hot pool", "hot pool", "pool"}),
        "Steam is rising from the warm waters.\n");
    add_item("steam", "It's evaporated water from from the pool.\n");
    add_item(({"cliff", "cliff face"}), "It might be a hundred feet"+
        " tall, and you think you see a ledge about halfway up.\n");
    add_item("ledge", "Yes, that's definately a ledge in the middle"+
        " of the cliff face.\n");

    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(FPATH + "env_hot_springs", "southeast", 0, 1);
    add_exit(FPATH + "quake_area", "north", 0, 1);
}