#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(34);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f42",
        "southwest" : "r01/f40",
        "south" : "r01/f41",
        "northwest" : "r03/f40",
        "east" : "r02/f42",
        "north" : "r03/f41",
        "northeast" : "r03/f42",
        "west" : "r02/f40",
    ]));
    
}
