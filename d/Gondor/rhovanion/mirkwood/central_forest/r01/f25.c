#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f26",
        "southwest" : "r00/f24",
        "south" : "r00/f25",
        "northwest" : "r02/f24",
        "east" : "r01/f26",
        "north" : "r02/f25",
        "northeast" : "r02/f26",
        "west" : "r01/f24",
    ]));
    
}
