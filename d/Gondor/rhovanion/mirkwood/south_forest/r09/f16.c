#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r10/f17",
        "southwest" : "r10/f15",
        "south" : "r10/f16",
        "northwest" : "r08/f15",
        "east" : "r09/f17",
        "north" : "r08/f16",
        "northeast" : "r08/f17",
        "west" : "r09/f15",
    ]));
    
}
