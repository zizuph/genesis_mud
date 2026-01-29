#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r05/f15",
        "southwest" : "r05/f13",
        "south" : "r05/f14",
        "northwest" : "r07/f13",
        "east" : "r06/f15",
        "north" : "r07/f14",
        "northeast" : "r07/f15",
        "west" : "r06/f13",
    ]));
    
}
