#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r38/f35",
        "southwest" : "r38/f33",
        "south" : "r38/f34",
        "northwest" : "r36/f33",
        "east" : "r37/f35",
        "north" : "r36/f34",
        "northeast" : "r36/f35",
        "west" : "r37/f33",
    ]));
    
}
