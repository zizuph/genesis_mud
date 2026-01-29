#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f17",
        "southwest" : "r08/f15",
        "south" : "r08/f16",
        "northwest" : "r10/f15",
        "east" : "r09/f17",
        "north" : "r10/f16",
        "northeast" : "r10/f17",
        "west" : "r09/f15",
    ]));
    
}
