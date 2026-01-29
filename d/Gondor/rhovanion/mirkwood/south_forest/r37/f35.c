#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r38/f36",
        "southwest" : "r38/f34",
        "south" : "r38/f35",
        "northwest" : "r36/f34",
        "east" : "r37/f36",
        "north" : "r36/f35",
        "northeast" : "r36/f36",
        "west" : "r37/f34",
    ]));
    
}
