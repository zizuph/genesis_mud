#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit MIRKWOOD_LIB_DIR + "follow_river";

public void drink_message(string from);

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(64);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r14/f20",
        "southwest" : "r14/f18",
        "south" : "r14/f19",
        "northwest" : "r16/f18",
        "east" : "r15/f20",
        "north" : "r16/f19",
        "northeast" : "r16/f20",
        "west" : "r15/f18",
    ]));
    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r14/f18", "southwest", "@@block@@",2,1);    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r15/f18", "west", "@@block@@",2,1);
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r14/f19", "south", "@@block@@",2,1);    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f18", "northwest", "@@block@@",2,1);

    add_long("To the west, you can see the wide, rushing waters of a " +
        "large river as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"river", "enchanted river"}),
        "Rushing north as it winds through the black trees from the " +
        "southeast is the legendary Enchanted river. This river is rumoured " +
        "to be cursed with an ancient elven magic which protects the " +
        "Woodland Realm.\n", LIGHT_ALL);

    set_river_name("enchanted river");
    add_follow_direction(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f19", "north", 
        "downstream towards the Woodland Realm");
    add_follow_direction(MIRKWOOD_CENTRAL_FOREST_DIR + "r14/f20", "southeast", 
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
write("The enchanted river is too wide to cross here, you will have to go in " +
    "a different direction.\n");
return 1;
}
