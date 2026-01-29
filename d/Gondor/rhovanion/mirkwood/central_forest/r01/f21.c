#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f22",
        "southwest" : "r00/f20",
        "south" : "r00/f21",
        "northwest" : "r02/f20",
        "east" : "r01/f22",
        "north" : "r02/f21",
        "northeast" : "r02/f22",
        "west" : "r01/f20",
    ]));
    
}
