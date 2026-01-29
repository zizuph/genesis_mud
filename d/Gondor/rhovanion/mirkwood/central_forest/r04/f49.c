#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f50",
        "southwest" : "r03/f48",
        "south" : "r03/f49",
        "northwest" : "r05/f48",
        "east" : "r04/f50",
        "north" : "r05/f49",
        "northeast" : "r05/f50",
        "west" : "r04/f48",
    ]));
    
}
