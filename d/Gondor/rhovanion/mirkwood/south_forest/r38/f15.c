#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r39/f16",
        "southwest" : "r39/f14",
        "south" : "r39/f15",
        "northwest" : "r37/f14",
        "east" : "r38/f16",
        "north" : "r37/f15",
        "northeast" : "r37/f16",
        "west" : "r38/f14",
    ]));
    
}
