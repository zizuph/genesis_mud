#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r34/f42",
        "southwest" : "r34/f40",
        "south" : "r34/f41",
        "northwest" : "r32/f40",
        "east" : "r33/f42",
        "north" : "r32/f41",
        "northeast" : "r32/f42",
        "west" : "r33/f40",
    ]));
    
}
