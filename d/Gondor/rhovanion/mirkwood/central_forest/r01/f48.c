#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f49",
        "southwest" : "r00/f47",
        "south" : "r00/f48",
        "northwest" : "r02/f47",
        "east" : "r01/f49",
        "north" : "r02/f48",
        "northeast" : "r02/f49",
        "west" : "r01/f47",
    ]));
    
}
