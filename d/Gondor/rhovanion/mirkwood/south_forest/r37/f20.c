#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r38/f21",
        "southwest" : "r38/f19",
        "south" : "r38/f20",
        "northwest" : "r36/f19",
        "east" : "r37/f21",
        "north" : "r36/f20",
        "northeast" : "r36/f21",
        "west" : "r37/f19",
    ]));
    
}
