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

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r18/f12",
        "east" : "r19/f12",
    ]));
    
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r17/f12", "south", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r17/f11", "southwest", "@@block@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r18/f11", "west", "@@block@@",2,1);

    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r17/f12", "north", "@@fore@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r17/f11", "northwest", "@@marsh@@",2,1);
    add_exit(MIRKWOOD_NORTH_FOREST_DIR + "r18/f11", "northeast", "@@fore@@",2,1);

    add_long("To the southwest, you can see the wide, rushing waters of a " +
        "large river as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"river", "forest river"}),
        "The cold, rushing waters of the forest river erupt from a dense " +
        "marsh which covers the ground to the northwest. The river is wide " +
        "and unpassable, as it travels southeast before it empties out " +
        "in Long Lake.\n", LIGHT_ALL);
    add_item_light(({"marsh", "dense marsh", "swamp"}),
        "It appears that the Forest river has kept the land here in a " +
        "permanent state of flooding, as a dense marsh spreads out as " +
        "far as you can see to the northwest. The swamp is so thick and " +
        "deep, it appears to be impassable for even the hardiest and " +
        "most experienced explorer.\n", LIGHT_ALL);

    set_river_name("forest river");
    add_follow_direction(MIRKWOOD_NORTH_FOREST_DIR + "r17/f13", "southeast", 
        "downstream towards Esgaroth");
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
fore()
{
write("The forest is just too thick to continue this way, you find yourself " +
    "back where you started. You will have to go in a different direction.\n");
return 1;
}

int
marsh()
{
write("A thick, dense marsh covers the ground to the northwest where the " +
    "river seems to floor the forest floor. You cannot see any way to " +
    "move any further to the northwest.\n");
return 1;
}