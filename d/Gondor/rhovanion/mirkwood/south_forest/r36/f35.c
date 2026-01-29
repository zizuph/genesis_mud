#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r37/f36",
        "southwest" : "r37/f34",
        "south" : "r37/f35",
        "northwest" : "r35/f34",
        "east" : "r36/f36",
        "north" : "r35/f35",
        "northeast" : "r35/f36",
        "west" : "r36/f34",
    ]));
    
}
