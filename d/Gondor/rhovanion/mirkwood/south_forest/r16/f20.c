#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r17/f21",
        "southwest" : "r17/f19",
        "south" : "r17/f20",
        "northwest" : "r15/f19",
        "east" : "r16/f21",
        "north" : "r15/f20",
        "northeast" : "r15/f21",
        "west" : "r16/f19",
    ]));
    
}
