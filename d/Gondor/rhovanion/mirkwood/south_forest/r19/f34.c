#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r20/f35",
        "southwest" : "r20/f33",
        "south" : "r20/f34",
        "northwest" : "r18/f33",
        "east" : "r19/f35",
        "north" : "r18/f34",
        "northeast" : "r18/f35",
        "west" : "r19/f33",
    ]));
    
}
