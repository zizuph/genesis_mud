#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit MIRKWOOD_LIB_DIR + "follow_river";

public void drink_message(string from);

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f30",
        "southwest" : "r04/f28",
        "south" : "r04/f29",
        "east" : "r05/f30",
    ]));
    
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r06/f28", "northwest", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r06/f29", "north", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r06/f30", "northeast", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r05/f28", "west", "@@ench@@",2,1);

    add_long("You are standing near two wide rivers which merge together " +
        "in a rushing crash of cold water immediately to the northwest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"forest river", "first river"}),
        "The cold, rushing waters of the forest river cut through the black " +
        "trees of Mirkwood here. The river is wide and unpassable, flowing " +
        "from the west to the east before it empties out into " +
        "Long Lake.\n", LIGHT_ALL);
    add_item_light(({"river", "rivers"}),
        "There are two rivers here, both of which cut and crash through " +
        "the forest as they merge before emptying out somewhere east of " +
        "Mirkwood forest.\n", LIGHT_ALL);
    add_item_light(({"enchanted river", "second river"}),
        "Rushing as it winds through the black trees from the " +
        "southwest is the legendary Enchanted " +
        "river. This river is rumoured to be full of an " +
        "ancient elven magic which protects the Woodland Realm.\n", LIGHT_ALL);

    set_river_name("forest river");
        add_follow_direction(MIRKWOOD_NORTH_FOREST_DIR + "r05/f30", "east", 
            "upstream, deeper into Mirkwood");
    set_river_name("enchanted river");
        add_follow_direction(MIRKWOOD_NORTH_FOREST_DIR + "r04/f28", "southwest", 
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

int
ench()
{
write("The enchanted river is too wide to cross here, you will have to go in " +
    "a different direction.\n");
return 1;
}
