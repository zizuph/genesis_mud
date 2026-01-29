#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f15",
        "southwest" : "r06/f13",
        "south" : "r06/f14",
        "northwest" : "r08/f13",
        "east" : "r07/f15",
        "north" : "r08/f14",
        "northeast" : "r08/f15",
        "west" : "r07/f13",
    ]));
    
}
