#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(41);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f35",
        "southwest" : "r00/f33",
        "south" : "r00/f34",
        "northwest" : "r02/f33",
        "east" : "r01/f35",
        "north" : "r02/f34",
        "northeast" : "r02/f35",
        "west" : "r01/f33",
    ]));
    
}
