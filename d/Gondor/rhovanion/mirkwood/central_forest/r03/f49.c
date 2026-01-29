#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f50",
        "southwest" : "r02/f48",
        "south" : "r02/f49",
        "northwest" : "r04/f48",
        "east" : "r03/f50",
        "north" : "r04/f49",
        "northeast" : "r04/f50",
        "west" : "r03/f48",
    ]));
    
}
