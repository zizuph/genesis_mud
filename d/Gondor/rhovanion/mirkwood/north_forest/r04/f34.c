#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit MIRKWOOD_LIB_DIR + "follow_river";

public void drink_message(string from);

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r03/f33",
        "south" : "r03/f34",
        "west" : "r04/f33",
    ]));



    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r05/f33", "northwest", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r05/f35", "northeast", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r05/f34", "north", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r04/f35", "east", "@@block@@",2,1);

    add_long("To the north, you can see the wide, rushing waters of a " +
        "large river as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"river", "forest river"}),
        "The cold, rushing waters of the forest river cut through the black " +
        "trees of Mirkwood here. The river is wide and unpassable, flowing " +
        "from the west into a deep canyon you cannot enter, to the southeast " +
        "before it empties out into Long Lake.\n", LIGHT_ALL);

    add_item_light(({"canyon", "deep canyon"}),
        "The forest river twists and dives into a deep canyon before winding " +
        "its way out of sight. It would be impossible to follow the river " +
        "to the southeast.\n", LIGHT_ALL);

    set_river_name("forest river");
    add_follow_direction(MIRKWOOD_NORTH_FOREST_DIR + "r04/f33", "west", 
        "upstream, deeper into Mirkwood");
}

void
init()
{
    ::init();
    init_drink();
    init_follow_river();
}

public void
drink_message(string from)
{
    write("You bend down and cup your hands to drink a mouthful of water from " 
        + "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.");
}
    
int
block()
{
write("The forest river is too wide to cross here, you will have to go in " +
    "a different direction.\n");
return 1;
}