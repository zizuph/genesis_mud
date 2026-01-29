#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r36/f35",
        "southwest" : "r36/f33",
        "south" : "r36/f34",
        "northwest" : "r34/f33",
        "east" : "r35/f35",
        "north" : "r34/f34",
        "northeast" : "r34/f35",
        "west" : "r35/f33",
    ]));
    
}
