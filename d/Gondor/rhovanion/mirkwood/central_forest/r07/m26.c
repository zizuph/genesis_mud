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
        "southeast" : "r06/m27",
        "southwest" : "r06/m25",
        "south" : "r06/m26",
        "northwest" : "r08/f25",
        "west" : "r07/f25",
    ]));
    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r07/m27", "east", "@@block@@",2,1);    
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r08/f27", "northeast", "@@block@@",2,1);
    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "r08/f26", "north", "@@block@@",2,1);

    add_long("To the northeast, you can see the wide, rushing waters of a " +
        "large river as it cuts through the forest.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"river", "enchanted river"}),
        "Rushing northwest as it winds through the black trees from the " +
        "southeast is the legendary Enchanted river. This river is rumoured " +
        "to be cursed with an ancient elven magic which protects the " +
        "Woodland Realm.\n", LIGHT_ALL);

    set_river_name("enchanted river");
    add_follow_direction(MIRKWOOD_CENTRAL_FOREST_DIR + "r08/f25", "northwest", 
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