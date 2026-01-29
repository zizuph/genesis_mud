#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r03/f43",
        "southwest" : "r03/f41",
        "south" : "r03/f42",
        "northwest" : "r01/f41",
        "east" : "r02/f43",
        "north" : "r01/f42",
        "northeast" : "r01/p43",
        "west" : "r02/f41",
    ]));
    
}
