#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f49",
        "southwest" : "r01/f47",
        "south" : "r01/f48",
        "northwest" : "r03/f47",
        "east" : "r02/f49",
        "north" : "r03/f48",
        "northeast" : "r03/f49",
        "west" : "r02/f47",
    ]));
    
}
