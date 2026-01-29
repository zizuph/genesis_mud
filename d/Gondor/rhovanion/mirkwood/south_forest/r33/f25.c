#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r34/f26",
        "southwest" : "r34/f24",
        "south" : "r34/f25",
        "northwest" : "r32/f24",
        "east" : "r33/f26",
        "north" : "r32/f25",
        "northeast" : "r32/f26",
        "west" : "r33/f24",
    ]));
    
}
