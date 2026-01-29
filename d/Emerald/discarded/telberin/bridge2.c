/*
 * The bridge that connects Telberin with the lake side road
 * Coded by Finwe
 * January 1997
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
 
void create_room()
{
    set_short("A bridge");
    set_long("@@long_desc@@");
 
    add_item(({"white object"}),
        "The large white object shines in the sunlight\n");
    add_item(({"bird", "birds"}),
        "All kinds of birds fly above you. You see gulls, " +
        "terns, kingfishes, and other birds that live on the water.\n");
    add_item("bridge", 
        "You stand on an ornate bridge. It is wide and constructed " +
        "thick planks of wood. You notice that the bridge can " +
        "easily be destroyed. What an odd idea. Maybe it's for " +
        "defence.\n");
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
 
    add_exit( THIS_DIR + "bridge3", "east");
    add_exit( THIS_DIR + "bridge1", "west");
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
        return "   The island begins to take shape as you " +
            "travel towards it. Patches of green emerge from it. " +
            "Glints of light twinkle on the island. From here, " +
            "you see a white object standing out against the blanket " +
            "of green on the island. It rises higher than the green " +
            "carpet. Birds can be seen flying from and to the " +
            "direction of the island.\n\n";
 
    if (from() == "west")
        return "   The shore is farther away. The trees " +
            "create a thin green ribon that snakes along the " +
            "edge of the lake. Barely in the distance, you can " +
            "see the crossroads. All around you is the surface " +
            "of the lake. Water sprays up occasionally as waves " +
            "crash against the edge of the bridge. Birds fly all " +
            "around you. Boats pass by you occasionally.\n\n";
 
   return "   You stand on a bridge that stretches east " +
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
