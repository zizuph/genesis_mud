#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r34/f22",
        "southwest" : "r34/f20",
        "south" : "r34/f21",
        "northwest" : "r32/f20",
        "east" : "r33/f22",
        "north" : "r32/f21",
        "northeast" : "r32/f22",
        "west" : "r33/f20",
    ]));
    
}
