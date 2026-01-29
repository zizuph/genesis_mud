inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "/d/Emerald/defs.h"
#include "default.h"
 
 
void create_room()
{
    set_short("A floating bridge");
    set_long("   You stand on a floating bridge. It stretchs " +
        "east out into the lake and west owards the shore. You " +
        "know that it must connect to something because of all " +
        "the traffic on it. Birds fly above you as they catch the " +
        "wind that blows past you. Waves lap at the edge of the " +
        "bridge, and occaisonally, a wave crashes into the " +
        "side, spraying water into the air.\n\n");
 
    add_item(({"bird", "birds"}),
        "All kinds of birds fly above you. You see gulls, " +
        "terns, kingfishes, and other birds that live on the water.\n");
    add_item(({"bridge", "floating bridge"}),
        "You stand on a bridge that rests on the water. The " +
        "constant motion of it is a little unsettling for a bit. " +
        "After a few minutes, you get used to the constant " +
        "motion of the bridge. The bridge is wide and constructed of " +
        "thick planks of wood. The platform rests on platoons\n");
 
    add_item(({"platoon", "platoons"}),
        "As you look over th edge, you see that the platoons " +
        " giant size drums.\n");
 
    add_item("east",
        "As you look east, an island rises from the water.\n");
    add_item("west", 
        "The shore is close by. You see the trees that line " +
        "the road, and the plants. Water laps gently at the shore.\n");
}
