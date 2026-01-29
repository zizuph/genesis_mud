#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r34/f44",
        "southwest" : "r34/f42",
        "south" : "r34/f43",
        "northwest" : "r32/f42",
        "east" : "r33/f44",
        "north" : "r32/f43",
        "northeast" : "r32/f44",
        "west" : "r33/f42",
    ]));
    
}
