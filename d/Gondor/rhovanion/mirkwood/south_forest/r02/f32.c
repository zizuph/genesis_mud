#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r03/f33",
        "southwest" : "r03/f31",
        "south" : "r03/f32",
        "northwest" : "r01/f31",
        "east" : "r02/f33",
        "north" : "r01/f32",
        "northeast" : "r01/f33",
        "west" : "r02/f31",
    ]));
    
}
