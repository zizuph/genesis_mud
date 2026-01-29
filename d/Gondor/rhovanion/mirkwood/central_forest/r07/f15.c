#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(39);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/f16",
        "southwest" : "r06/f14",
        "south" : "r06/f15",
        "northwest" : "r08/f14",
        "east" : "r07/f16",
        "north" : "r08/f15",
        "northeast" : "r08/f16",
        "west" : "r07/f14",
    ]));
    
}
