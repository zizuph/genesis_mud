#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(6);
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
