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
 
    add_item("arch",
        "The arch seems quite large from this distance.\n");
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
    add_item("debris",
        "You see bits of seaweed, sticks, and other things found " +
        "floating on a lake.\n");
    add_item(({"seaweed", "sticks", "driftwood"}),
        "It is dead looking as it floats past you on the lake.\n");
 
    set_alarm(1.0,0.0,"reset_room");
 
    add_exit( THIS_DIR + "landing", "east");
    add_exit( THIS_DIR + "bridge3", "west");
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
        return "   You see many trees on the island. Beautiful " +
            "houses line the avenues. They are tall and elegant, " +
            "reflecting the tastes of the inhabitants. The roofs " +
            "of the houses catch the sunlight and sparkle in the " +
            "sun. Guards weapons can be seen twinkling in the " +
            "sunlight as the guards patrol the island. A large " +
            "arch looms before the city. Birds fly around the " +
            "island.\n\n";
 
 
    if (from() == "west")
        return "   The lake fills your view. It stretches " + 
            "out forever. Boats float by as elves fish the water " +
            "for food. Debris floats by on the surf. Birds fly past " +
            "occaisonally. Waves lap at the bridge and occasionally, " +
            "a wave crashes into the side, spraying you with water.\n\n";
 
   return "   You stand on a bridge that stretches east " +
        "into the lake and west towards the shore. You " +
        "know that it must connect to something because of all " +
        "the traffic on it. Birds fly above you as they catch the " +
        "wind that blows past you. Waves lap at the edge of the " +
        "bridge, and occaisonally, a wave crashes into the " +
        "side, spraying water into the air.\n\n";
 
}
void
reset_room()
{
}
