#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r34/f11",
        "southwest" : "r34/f09",
        "south" : "r34/f10",
        "northwest" : "r32/f09",
        "east" : "r33/f11",
        "north" : "r32/f10",
        "northeast" : "r32/f11",
        "west" : "r33/f09",
    ]));
    
}
