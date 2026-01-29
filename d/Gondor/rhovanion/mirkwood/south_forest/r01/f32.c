#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f33",
        "southwest" : "r02/f31",
        "south" : "r02/f32",
        "northwest" : "r00/f31",
        "east" : "r01/f33",
        "north" : "r00/f32",
        "northeast" : "r00/f33",
        "west" : "r01/f31",
    ]));
    
}
