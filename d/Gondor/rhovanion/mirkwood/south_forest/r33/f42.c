#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r34/f43",
        "southwest" : "r34/f41",
        "south" : "r34/f42",
        "northwest" : "r32/f41",
        "east" : "r33/f43",
        "north" : "r32/f42",
        "northeast" : "r32/f43",
        "west" : "r33/f41",
    ]));
    
}
