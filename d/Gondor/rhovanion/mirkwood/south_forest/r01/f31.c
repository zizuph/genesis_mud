#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r02/f32",
        "southwest" : "r02/f30",
        "south" : "r02/f31",
        "northwest" : "r00/f30",
        "east" : "r01/f32",
        "north" : "r00/f31",
        "northeast" : "r00/f32",
        "west" : "r01/f30",
    ]));
    
}
