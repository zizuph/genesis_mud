#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southeast" : "r37/f14",
        "southwest" : "r37/f12",
        "south" : "r37/f13",
        "northwest" : "r35/f12",
        "east" : "r36/f14",
        "north" : "r35/f13",
        "northeast" : "r35/f14",
    ]));
    
}
