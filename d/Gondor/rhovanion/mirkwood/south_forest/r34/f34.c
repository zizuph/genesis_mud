#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r35/f35",
        "southwest" : "r35/f33",
        "south" : "r35/f34",
        "northwest" : "r33/f33",
        "east" : "r34/f35",
        "north" : "r33/f34",
        "northeast" : "r33/f35",
        "west" : "r34/f33",
    ]));
    
}
