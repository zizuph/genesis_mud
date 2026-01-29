#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r07/f16",
        "southwest" : "r07/f14",
        "south" : "r07/f15",
        "northwest" : "r09/f14",
        "east" : "r08/f16",
        "north" : "r09/f15",
        "northeast" : "r09/f16",
        "west" : "r08/f14",
    ]));
    
}
