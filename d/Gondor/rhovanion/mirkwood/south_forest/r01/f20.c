#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f21",
        "southwest" : "r02/f19",
        "south" : "r02/f20",
        "northwest" : "r00/f19",
        "east" : "r01/f21",
        "north" : "r00/f20",
        "northeast" : "r00/f21",
        "west" : "r01/f19",
    ]));
    
}
