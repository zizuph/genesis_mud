#include "../../defs.h";
#include <stdproperties.h>

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() 

{

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    add_long("Upon a small rise here, a tall pine tree is growing up out " +
        "of a cluster of juniper bushes.",
        ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    add_item_light(({"tree", "pine", "pine tree", "tall tree", "tall pine tree"}),
        "This pine tree rises high out of a cluster of juniper bushes " +
        "which is growing on a small rise just in front of you. Nestled in " +
        "the branches, you can just make out a small, brown bird's nest. " +
        "The nest is just low enough that you could peek inside.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"bushes", "juniper", "juniper bush", "juniper bushes", "spiky bushes", "spiky green bushes", "spiky green juniper bushes", "green bushes", "green juniper bushes"}),
        "This is a large mass of spiky, green juniper bushes is clustered beneath a " +
        "tall pine tree. Hundreds of small, blue berries are growing all over the bushes.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"berries", "blue berries", "blue berry", "juniper berries", "juniper berry"}),
        "These pale, blue juniper berries are growing abundantly all over the " +
        "juniper bushes. The berries sort of look like slightly dusty blueberries, " +
        "but since they are not good to eat, you think it would be better to " +
        "leave them alone.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));
    add_item_light(({"rise", "small rise", "hill", "small hill"}),
        "The ground here swells slightly as it rises up to peak in a small " +
        "hill here before you. Atop the rise, a large cluster of " +
        "green juniper bushes huddle around the base of the tall pine " +
        "tree which reaches up to the forest ceiling.\n", ({LIGHT_MIDDAY, LIGHT_BRIGHT}));

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r17/f20",
        "southwest" : "r17/f18",
        "south" : "r17/f19",
        "northwest" : "r19/f18",
        "east" : "r18/f20",
        "north" : "r19/f19",
        "northeast" : "r19/f20",
        "west" : "r18/f18",

    ]));
    
    setuid();
    seteuid(getuid());
    object nest = clone_object(MIRKWOOD_OBJ_DIR + "north_forest/birds_nest_1");
    nest->move(this_object());
}
