#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r39/f15",
        "southwest" : "r39/f13",
        "south" : "r39/f14",
        "northwest" : "r37/f13",
        "east" : "r38/f15",
        "north" : "r37/f14",
        "northeast" : "r37/f15",
        "west" : "r38/f13",
    ]));
    
}
