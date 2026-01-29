#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r32/f21",
        "southwest" : "r32/f19",
        "south" : "r32/f20",
        "northwest" : "r30/f19",
        "east" : "r31/f21",
        "north" : "r30/f20",
        "northeast" : "r30/f21",
        "west" : "r31/f19",
    ]));
    
}
