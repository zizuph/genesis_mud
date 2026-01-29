#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(34);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r00/f32",
        "southwest" : "r00/f30",
        "south" : "r00/f31",
        "northwest" : "r02/f30",
        "east" : "r01/f32",
        "north" : "r02/f31",
        "northeast" : "r02/f32",
        "west" : "r01/f30",
    ]));
    
}
