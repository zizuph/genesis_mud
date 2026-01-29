#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f20",
        "southwest" : "r00/f18",
        "south" : "r00/f19",
        "northwest" : "r02/f18",
        "east" : "r01/f20",
        "north" : "r02/f19",
        "northeast" : "r02/f20",
        "west" : "r01/f18",
    ]));
    
}
