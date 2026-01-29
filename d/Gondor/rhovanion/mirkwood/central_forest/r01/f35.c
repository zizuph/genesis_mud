#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(41);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f36",
        "southwest" : "r00/f34",
        "south" : "r00/f35",
        "northwest" : "r02/f34",
        "east" : "r01/f36",
        "north" : "r02/f35",
        "northeast" : "r02/f36",
        "west" : "r01/f34",
    ]));
    
}
