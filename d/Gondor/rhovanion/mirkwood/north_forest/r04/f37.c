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

        "northwest" : "r05/f36",
        "north" : "r05/f37",
        "west" : "r04/f36",
    ]));

    add_exit(MIRKWOOD_ELFPATH_DIR + "p37", "south", "@@block@@",2,1);
    add_exit(MIRKWOOD_ELFPATH_DIR + "p38", "southeast", "@@block@@",2,1);
    add_exit(MIRKWOOD_ELFPATH_DIR + "p36", "southwest", "@@block@@",2,1);

    add_long("To the south, you can see the wide, rushing waters of a " +
        "large river as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_exit("f37", "east", "@@exit@@",2,1);
    add_exit("f37", "northeast", "@@exit@@",2,1);

    add_item_light(({"river", "forest river"}),
        "The rushing waters of the forest river wind their way east " +
        "towards Esgaroth.\n", LIGHT_ALL);

    set_river_name("forest river");
    add_follow_direction(MIRKWOOD_NORTH_FOREST_DIR + "r04/f36", "west", 
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
exit()
{
write("The forest is just too thick to continue this way, you find " +
    "yourself back where you started. You will have to go in a different " +
    "direction.\n");
return 1;
}