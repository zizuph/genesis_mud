#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r33/f35",
        "southwest" : "r33/f33",
        "south" : "r33/f34",
        "northwest" : "r31/f33",
        "east" : "r32/f35",
        "north" : "r31/f34",
        "northeast" : "r31/f35",
        "west" : "r32/f33",
    ]));
    
}
