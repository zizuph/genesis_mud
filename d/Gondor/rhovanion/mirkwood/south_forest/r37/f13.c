#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r38/f14",
        "southwest" : "r38/f12",
        "south" : "r38/f13",
        "east" : "r37/f14",
        "north" : "r36/f13",
        "northeast" : "r36/f14",
        "west" : "r37/f12",
    ]));
    
}
