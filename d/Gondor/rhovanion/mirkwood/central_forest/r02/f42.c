#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f43",
        "southwest" : "r01/f41",
        "south" : "r01/f42",
        "northwest" : "r03/f41",
        "east" : "r02/f43",
        "north" : "r03/f42",
        "northeast" : "r03/f43",
        "west" : "r02/f41",
    ]));
    
}
