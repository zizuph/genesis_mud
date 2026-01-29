#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f50",
        "southwest" : "r00/f48",
        "south" : "r00/f49",
        "northwest" : "r02/f48",
        "east" : "r01/f50",
        "north" : "r02/f49",
        "northeast" : "r02/f50",
        "west" : "r01/f48",
    ]));
    
}
