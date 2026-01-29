#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f44",
        "southwest" : "r00/f42",
        "south" : "r00/f43",
        "northwest" : "r02/f42",
        "east" : "r01/f44",
        "north" : "r02/f43",
        "northeast" : "r02/f44",
        "west" : "r01/f42",
    ]));
    
}
