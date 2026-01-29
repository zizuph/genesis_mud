#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f11",
        "southwest" : "r01/f09",
        "south" : "r01/f10",
        "northwest" : "r03/f09",
        "east" : "r02/f11",
        "north" : "r03/f10",
        "northeast" : "r03/f11",
        "west" : "r02/f09",
    ]));
    
}
