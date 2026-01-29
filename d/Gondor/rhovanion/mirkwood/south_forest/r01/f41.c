#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f42",
        "southwest" : "r02/f40",
        "south" : "r02/f41",
        "northwest" : "r00/f40",
        "east" : "r01/f42",
        "north" : "r00/f41",
        "northeast" : "r00/p42",
        "west" : "r01/f40",
    ]));
    
}
