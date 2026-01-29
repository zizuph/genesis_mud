/*
 * Room of the Old Road in Mirkwood.
 *
 */

#include "../defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

inherit MIRKWOOD_OLDROAD_DIR + "base";

/*
 * Function name: create_mirkwood_road_room
 * Description  : Create this room of the old road
 */
void create_mirkwood_road_room()
{
    // Force the randomized messages to always be the same for roads
    set_room_seed(14);
    set_mirkwood_location(LOCATION_MIDDLE);
    
    ::create_mirkwood_road_room();

    set_add_wildlife();

    set_short("You are on the Old Road somewhere " +
        "in the middle of Mirkwood Forest");

    add_long("Sitting along the north side of the road, is a large, " +
        "flat boulder. ",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"boulder", "flat boulder"}),
        "This long, flat boulder is resting right on the side of the road. " +
        "It is mostly grey in colour, with a bright vein of clear " +
        "quartz running along the eastern edge. The top of the boulder " +
        "seems to be mostly flat, although it is a bit hard to tell " +
        "since it is almost seven feet high.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    
    add_exit("r15", "east");
    add_exit("r13", "west");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f18", "northwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f19", "north");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r00/f20", "northeast");
    
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f18", "southwest");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f19", "south");
    add_forest_entrance(MIRKWOOD_SOUTH_FOREST_DIR + "r00/f20", "southeast");
}

public int climb_up() {
    if (this_player()->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_CLIMB })) <= 0) {
        write("As you try to get a handhold, you tumble down to the ground!\n");
        say(QCTNAME(TP) + " tries to climb up the boulder, but " 
            + this_player()->query_pronoun() + " loses " 
            + this_player()->query_possessive() + " grip and tumbles to "
            + "the ground.\n");
        return 1;
    }

    write("You manage to climb up to the top of the boulder.\n");
    say(QCTNAME(this_player()) + " scrambles up to the top of the boulder.\n");

    this_player()->move_living("M", MIRKWOOD_OLDROAD_DIR + "boulder", 1);
    say(QCTNAME(this_player()) + " scrambles up the boulder.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(climb_up, "climb");
}
