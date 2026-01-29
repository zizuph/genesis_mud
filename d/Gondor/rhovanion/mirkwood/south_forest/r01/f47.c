#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f48",
        "southwest" : "r02/f46",
        "south" : "r02/f47",
        "northwest" : "r00/f46",
        "east" : "r01/f48",
        "north" : "r00/f47",
        "northeast" : "r00/f48",
        "west" : "r01/f46",
    ]));
    
}
