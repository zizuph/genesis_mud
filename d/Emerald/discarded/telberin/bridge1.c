inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
 
void create_room()
{
    set_short("A bridge");
    set_long("@@long_desc@@");
 
    add_item(({"bird", "birds"}),
        "All kinds of birds fly above you. You see gulls, " +
        "terns, kingfishes, and other birds that live on the water.\n");
    add_item("bridge",
        "You stand on an ornate bridge. It is wide and constructed " +
        "thick planks of wood. You notice that the bridge can " +
        "easily be destroyed. What an odd idea. Maybe it's for " +
        "defence.\n");
    add_item("east",
        "As you look east, an island rises from the water.\n");
    add_item("west", 
        "The shore is close by. You see the trees that line " +
        "the road, and the plants. Water laps gently at the shore.\n");
    add_item("lake",
        "The water of the lake is a deep blue, almost midnight " +
        "black in color. The surface is alive as birds swoop " +
        "down to catch a meal. Out on the lake, you see " +
        "boats, presumably fishing vessels.\n");
    add_item(({"plank", "planks", "wood"}),
        "The planks of the bridge are constructed from wood " +
        "that has been waterproofed. They don't show signs of rot " +
        "or decay and look to be in excellent condition. You don't " +
        "detect any seams where the wood was joined together, but " +
        "you still feel secure on the bridge.\n");
 
    set_alarm(1.0,0.0,"reset_room");
 
    add_exit( THIS_DIR   + "bridge2", "east");
    add_exit(LROAD_DIR + "xroad", "west");
}
 
/* Function: from
 * Returns:  returns the last direction this_player typed
 */
string
from()
{
   return this_player()->query_prop(LIVE_S_LAST_MOVE);
}
 
string
long_desc()
{
    if (from() == "east")
        return "   As you travel east, a large island looms into " +
            "view. It grows in size as you approach it. Not " +
            "much can be seen as mists swirl about it. It sits " +
            "like a fist jutting out of the water as it rises " +
            "from the lake's surface. Little specks can be seen " +
            "floating on the water, probably boats. Birds fly " +
            "about the lake, catching a meal or playing in the " +
            "currents that rise from the lake.\n\n";
 
    if (from() == "west")
        return "   The crossroad can be seen from here. It " +
            "stands out as the road passes by it. Trees surround " +
            "the area like a green frame as they line the shore, " +
            "preventing a clear view of the road. Occaisonally " +
            "a traveller comes into view as they pass through " +
            "the crossroads. The water laps at the lake's edge " +
            "as waterfowl bob on the surface.\n\n";
 
    return "   You stand on a bridge that stretches east "+
        "into the lake and west towards the shore. You " +
        "know that it must connect to something because of all " +
        "the traffic on it. Birds fly above you as they catch the " +
        "wind that blows past you. Waves lap at the edge of the " +
        "bridge, and occasionally, a wave crashes into the " +
        "side, spraying water into the air.\n\n";
 
}
void
reset_room()
{
}
