#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r35/f21",
        "southwest" : "r35/f19",
        "south" : "r35/f20",
        "northwest" : "r33/f19",
        "east" : "r34/f21",
        "north" : "r33/f20",
        "northeast" : "r33/f21",
        "west" : "r34/f19",
    ]));
    
}
