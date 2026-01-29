#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r37/f21",
        "southwest" : "r37/f19",
        "south" : "r37/f20",
        "northwest" : "r35/f19",
        "east" : "r36/f21",
        "north" : "r35/f20",
        "northeast" : "r35/f21",
        "west" : "r36/f19",
    ]));
    
}
