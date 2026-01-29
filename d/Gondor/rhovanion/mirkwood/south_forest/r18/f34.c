#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r19/f35",
        "southwest" : "r19/f33",
        "south" : "r19/f34",
        "northwest" : "r17/f33",
        "east" : "r18/f35",
        "north" : "r17/f34",
        "northeast" : "r17/f35",
        "west" : "r18/f33",
    ]));
    
}
