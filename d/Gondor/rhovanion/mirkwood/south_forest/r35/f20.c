#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r36/f21",
        "southwest" : "r36/f19",
        "south" : "r36/f20",
        "northwest" : "r34/f19",
        "east" : "r35/f21",
        "north" : "r34/f20",
        "northeast" : "r34/f21",
        "west" : "r35/f19",
    ]));
    
}
