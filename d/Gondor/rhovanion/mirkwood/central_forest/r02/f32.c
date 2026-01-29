#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(71);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r01/f33",
        "southwest" : "r01/f31",
        "south" : "r01/f32",
        "northwest" : "r03/f31",
        "east" : "r02/f33",
        "north" : "r03/f32",
        "northeast" : "r03/f33",
        "west" : "r02/f31",
    ]));
    
}
