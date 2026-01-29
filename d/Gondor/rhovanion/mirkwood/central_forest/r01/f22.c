#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f23",
        "southwest" : "r00/f21",
        "south" : "r00/f22",
        "northwest" : "r02/f21",
        "east" : "r01/f23",
        "north" : "r02/f22",
        "northeast" : "r02/f23",
        "west" : "r01/f21",
    ]));
    
}
