#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f34",
        "southwest" : "r00/f32",
        "south" : "r00/f33",
        "northwest" : "r02/f32",
        "east" : "r01/f34",
        "north" : "r02/f33",
        "northeast" : "r02/f34",
        "west" : "r01/f32",
    ]));
    
}
