#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r34/f33",
        "southwest" : "r34/f31",
        "south" : "r34/f32",
        "northwest" : "r32/f31",
        "east" : "r33/f33",
        "north" : "r32/f32",
        "northeast" : "r32/f33",
        "west" : "r33/f31",
    ]));
    
}
