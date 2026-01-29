/*
 * coded by Amelia 6/1/97
 * path through Ten Alders
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
#include <stdproperties.h>

public void
create_earthsea_room()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    set_short("Mountain cliff edge");
    set_long("You emerge from the dark green forest to find yourself " +
        "staring over the narrow ledge of a tall cliff. You feel a " +
        "slight sense of vertigo as you look far down the mountain " +
        "all the way to the seacoast. The path " +
        "bends sharply to the north here. To the " +
        "south is a dropoff looking out over the grey-blue sea far " +
        "below. You realize you are standing at a dizzying height, " +
        "but the view is spectacular.\n");
    add_item((({"sea", "blue sea", "view", "ledge", "cliff" })),
        "You realize you are standing on a ledge atop a tall " +
        "limestone cliff that overlooks Gont Sea. Far below you " +
        "see three longships at anchor in the bay, whose red " +
        "sails bear the mark of Karego-At.\n");
    add_exit("south_path_15", "north");
    add_exit("south_path_17", "southwest");
}
