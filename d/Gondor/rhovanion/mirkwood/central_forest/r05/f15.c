#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(35);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r04/f16",
        "southwest" : "r04/f14",
        "south" : "r04/f15",
        "northwest" : "r06/f14",
        "east" : "r05/f16",
        "north" : "r06/f15",
        "northeast" : "r06/f16",
        "west" : "r05/f14",
    ]));
    
}
