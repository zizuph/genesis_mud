#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>
#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit MIRKWOOD_LIB_DIR + "follow_river";

public void drink_message(string from);


void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r06/m28",
        "southwest" : "r06/m26",
        "south" : "r06/m27",
        "northwest" : "r08/f26",
        "east" : "r07/f28",
        "north" : "r08/f27",
        "northeast" : "r08/f28",
    ]));

    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "caves/cave1", "enter",0,2,1);
    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r07/m26", "west", "@@block@@",2,1);   

    add_long("To the west, you can see the wide, rushing waters of a " +
        "large river, spilling out from the mountain beside a dark cave, " +
        "as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"river", "enchanted river"}),
        "A wide river gushes out from the mountainside, before it begins " +
        "to cut a path northwest through the forest. The enchanted river is " +
        "rumoured to be cursed with an ancient elven magic which protects " +
        "the Woodland Realm.\n", LIGHT_ALL);
    add_item_light(({"cave", "dark cave"}),
        "Right beside the river, there appears to be a dark cave which " +
        "begins to tunnel into the mountainside. It is so dark, that you " +
        "cannot see much aside from getting a sense that it dives almost " +
        "straight down, deep into the ground. If you were brave enough, " +
        "or foolish enough, you might want to enter it.\n", LIGHT_ALL);

    set_river_name("enchanted river");
    add_follow_direction(MIRKWOOD_CENTRAL_FOREST_DIR + "r08/f26", "northwest", 
        "downstream towards the Woodland Realm");
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