#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r34/f41",
        "southwest" : "r34/f39",
        "south" : "r34/f40",
        "northwest" : "r32/f39",
        "east" : "r33/f41",
        "north" : "r32/f40",
        "northeast" : "r32/f41",
        "west" : "r33/f39",
    ]));
    
}
