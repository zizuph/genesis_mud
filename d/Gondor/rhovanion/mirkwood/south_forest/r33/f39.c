#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r34/f40",
        "southwest" : "r34/f38",
        "south" : "r34/f39",
        "northwest" : "r32/f38",
        "east" : "r33/f40",
        "north" : "r32/f39",
        "northeast" : "r32/f40",
        "west" : "r33/f38",
    ]));
    
}
