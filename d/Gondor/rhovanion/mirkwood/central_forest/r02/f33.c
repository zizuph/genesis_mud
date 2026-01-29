#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(75);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f34",
        "southwest" : "r01/f32",
        "south" : "r01/f33",
        "northwest" : "r03/f32",
        "east" : "r02/f34",
        "north" : "r03/f33",
        "northeast" : "r03/f34",
        "west" : "r02/f32",
    ]));
    
}
