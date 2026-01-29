#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r34/f21",
        "southwest" : "r34/f19",
        "south" : "r34/f20",
        "northwest" : "r32/f19",
        "east" : "r33/f21",
        "north" : "r32/f20",
        "northeast" : "r32/f21",
        "west" : "r33/f19",
    ]));
    
}
