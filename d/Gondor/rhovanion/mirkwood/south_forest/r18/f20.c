#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r19/f21",
        "southwest" : "r19/f19",
        "south" : "r19/f20",
        "northwest" : "r17/f19",
        "east" : "r18/f21",
        "north" : "r17/f20",
        "northeast" : "r17/f21",
        "west" : "r18/f19",
    ]));
    
}
