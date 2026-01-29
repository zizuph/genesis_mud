#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r37/f35",
        "southwest" : "r37/f33",
        "south" : "r37/f34",
        "northwest" : "r35/f33",
        "east" : "r36/f35",
        "north" : "r35/f34",
        "northeast" : "r35/f35",
        "west" : "r36/f33",
    ]));
    
}
