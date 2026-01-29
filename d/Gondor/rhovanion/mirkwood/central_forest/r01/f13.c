#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f14",
        "southwest" : "r00/f12",
        "south" : "r00/f13",
        "northwest" : "r02/f12",
        "east" : "r01/f14",
        "north" : "r02/f13",
        "northeast" : "r02/f14",
        "west" : "r01/f12",
    ]));
    
}
