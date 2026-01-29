#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f34",
        "southwest" : "r02/f32",
        "south" : "r02/f33",
        "northwest" : "r00/f32",
        "east" : "r01/f34",
        "north" : "r00/f33",
        "northeast" : "r00/f34",
        "west" : "r01/f32",
    ]));
    
}
