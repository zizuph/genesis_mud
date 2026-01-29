#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f33",
        "southwest" : "r04/f31",
        "south" : "r04/f32",
        "northwest" : "r02/f31",
        "east" : "r03/f33",
        "north" : "r02/f32",
        "northeast" : "r02/f33",
        "west" : "r03/f31",
    ]));
    
}
