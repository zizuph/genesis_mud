#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f34",
        "southwest" : "r04/f32",
        "south" : "r04/f33",
        "northwest" : "r02/f32",
        "east" : "r03/f34",
        "north" : "r02/f33",
        "northeast" : "r02/f34",
        "west" : "r03/f32",
    ]));
    
}
