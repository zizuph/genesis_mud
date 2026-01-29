#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southeast" : "r38/f13",
        "southwest" : "r38/f11",
        "south" : "r38/f12",
        "northwest" : "r36/f11",
        "east" : "r37/f13",
        "northeast" : "r36/f13",
        "west" : "r37/p11",
    ]));
    
}
