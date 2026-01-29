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

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "north"     : MIRKWOOD_ELFPATH_DIR + "p18",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p19",

        "southwest" : "r15/f17",
        "northwest" : "r17/f17",
        "east" : "r16/f19",
        "west" : "r16/f17",
    ]));
    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f19", "east", "@@block@@",2,1);    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r15/f19", "southeast", "@@block@@",2,1);

    add_long("To the east, you can see the wide, rushing waters of a " +
        "large river as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"river", "enchanted river"}),
        "Rushing northeast as it winds through the black trees from the " +
        "south is the legendary Enchanted river. This river is rumoured " +
        "to be cursed with an ancient elven magic which protects the " +
        "Woodland Realm.\n", LIGHT_ALL);

    set_river_name("enchanted river");
    add_follow_direction(MIRKWOOD_ELFPATH_DIR + "p19", "northeast", 
        "downstream towards the Woodland Realm");
    add_follow_direction(MIRKWOOD_CENTRAL_FOREST_DIR + "r15/f18", "south", 
        "upstream, to the Elf Path in Mirkwood");
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