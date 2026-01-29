#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r34/f35",
        "southwest" : "r34/f33",
        "south" : "r34/f34",
        "northwest" : "r32/f33",
        "east" : "r33/f35",
        "north" : "r32/f34",
        "northeast" : "r32/f35",
        "west" : "r33/f33",
    ]));
    
}
