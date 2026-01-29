#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f21",
        "southwest" : "r00/f19",
        "south" : "r00/f20",
        "northwest" : "r02/f19",
        "east" : "r01/f21",
        "north" : "r02/f20",
        "northeast" : "r02/f21",
        "west" : "r01/f19",
    ]));
    
}
