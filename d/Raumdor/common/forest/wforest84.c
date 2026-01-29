/* West Forest Room, Sarr. 
 * Updated, Nerull.
 * 2017-05-24 Malus: Added description*/
/* 2017-08-28 Malus: Moving contents beneath bridge to make path safe */ 
#include "defs.h"
#include <tasks.h>
inherit FOREST_ROAD_ROOM;

int do_climb(string str);

void
create_room()
{
    ::create_room();
    set_short("Above a bridge along an old path");
    set_long("You stand above a stone bridge, connected to an old pathway " +
            "through a shadowy forest. The bridge amply spans a stream " +
            "that flows through here and partly conceals it from view. The " +
            "road continues at each end the bridge, east and west, and all " +
            "other directions lead into the trees.\n");  
    add_item(({"stream"}), "The streams flows down from the high mountains"+
    " at the south to the north into the forest.\n");
    add_item(({"bridge"}), "The stone is old, but sturdy. The rough cuts " +
            "suggest you might able to climb down the side. Perhaps it is " +
            "a trick of the shadows, but you sense something moving in " +
            "the darkness below.\n");
    add_item(({"darkness"}), "Shadows surround you, but the underside of " +
            "the bridge is particularly mysterious.\n");
    add_item(({"forest", "trees"}), "The forest is dark and gloomy.\n");
    add_item(({"ruins"}), "Looks like a circle of stone.\n");
    add_item(({"tree", "branch", "heavy branch", "thick branch"}), 
            "A thick branch on one of the many trees here is being used " +
            "to suspend a cage off the ground.\n");
    
    add_exit(FOREST_DIR + "nforest04","north",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "nforest05","northeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest85","east");
    add_exit(FOREST_DIR + "wforest71","southeast",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest70","south",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest69","southwest",0,FOREST_FATIGUE);
    add_exit(FOREST_DIR + "wforest83","west");
    add_exit(FOREST_DIR + "nforest03","northwest",0,FOREST_FATIGUE);
}

init()
{
    ::init();
    add_action("drink", "drink");
    add_action(do_climb, "climb");
}

int
drink(string str)
{
    object obj = TP;
    if (str == "from stream")
    {
        write("It's out of reach, beneath the bridge. You will " +
            "have to get closer.\n");
        return 1;
    }
    notify_fail("Drink from what? The stream?\n");
    return 0;
}

int
do_climb(string str)
{
    if (!strlen(str))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(str, ({}), " [down] [the] [stone] 'bridge'")
            && str != "down")
    {
        notify_fail("Climb where? Down the stone bridge?\n");
        return 0;
    }

    if (TP->resolve_task(TASK_ROUTINE, ({SS_CLIMB, TS_STR, TS_DEX})))
    {
        write("You lower yourself down the side of the bridge.\n");
        say(({
            METNAME + " climbs down the side of the bridge.\n",
            TART_NONMETNAME + " climbs down the side of the bridge.\n",
            "You hear the sounds of someone climbing down the bridge.\n"
        }));
        TP->move_living("M", FOREST_DIR + "under_bridge", 1);
        say(({
            METNAME + " climbs down from above.\n",
            ART_NONMETNAME + " climbs down from above.\n",
            "You hear sounds of movement down the side of the bridge.\n"
        }));
    }
    else
    {
        write("You try to lower yourself down the side of the bridge, " +
               "but fail to find a good foothold.\n");
        say(({
            METNAME + " tries to climb down the side of the bridge, " +
            "but fails.\n",
            TART_NONMETNAME + " tries to climb down the side of the bridge, " +
            "but fails.\n",
            "You hear the sound of movement near the side of the bridge.\n"
        }));
    }
    return 1;
}

