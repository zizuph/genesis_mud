#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r03/f49",
        "southwest" : "r03/f47",
        "south" : "r03/f48",
        "northwest" : "r05/f47",
        "east" : "r04/f49",
        "north" : "r05/f48",
        "northeast" : "r05/f49",
        "west" : "r04/f47",
    ]));
    
}
