#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f16",
        "southwest" : "r08/f14",
        "south" : "r08/f15",
        "northwest" : "r06/f14",
        "east" : "r07/f16",
        "north" : "r06/f15",
        "northeast" : "r06/f16",
        "west" : "r07/f14",
    ]));
    
}
