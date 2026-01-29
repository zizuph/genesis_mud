#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r16/f15",
        "southwest" : "r16/f13",
        "south" : "r16/f14",
        "northwest" : "r14/f13",
        "east" : "r15/f15",
        "north" : "r14/f14",
        "northeast" : "r14/f15",
        "west" : "r15/f13",
    ]));
    
}
