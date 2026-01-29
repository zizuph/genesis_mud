#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r34/f36",
        "southwest" : "r34/f34",
        "south" : "r34/f35",
        "northwest" : "r32/f34",
        "east" : "r33/f36",
        "north" : "r32/f35",
        "northeast" : "r32/f36",
        "west" : "r33/f34",
    ]));
    
}
