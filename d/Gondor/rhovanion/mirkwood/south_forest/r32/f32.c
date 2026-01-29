#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r33/f33",
        "southwest" : "r33/f31",
        "south" : "r33/f32",
        "northwest" : "r31/f31",
        "east" : "r32/f33",
        "north" : "r31/f32",
        "northeast" : "r31/f33",
        "west" : "r32/f31",
    ]));
    
}
