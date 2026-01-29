#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r34/f32",
        "southwest" : "r34/f30",
        "south" : "r34/f31",
        "northwest" : "r32/f30",
        "east" : "r33/f32",
        "north" : "r32/f31",
        "northeast" : "r32/f32",
        "west" : "r33/f30",
    ]));
    
}
