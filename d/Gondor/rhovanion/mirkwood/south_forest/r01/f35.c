#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f36",
        "southwest" : "r02/f34",
        "south" : "r02/f35",
        "northwest" : "r00/f34",
        "east" : "r01/f36",
        "north" : "r00/f35",
        "northeast" : "r00/f36",
        "west" : "r01/f34",
    ]));
    
}
