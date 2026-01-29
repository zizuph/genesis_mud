#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f40",
        "southwest" : "r00/f38",
        "south" : "r00/f39",
        "northwest" : "r02/f38",
        "east" : "r01/f40",
        "north" : "r02/f39",
        "northeast" : "r02/f40",
        "west" : "r01/f38",
    ]));
    
}
