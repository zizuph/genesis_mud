#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r38/f17",
        "southwest" : "r38/f15",
        "south" : "r38/f16",
        "northwest" : "r36/f15",
        "east" : "r37/f17",
        "north" : "r36/f16",
        "northeast" : "r36/f17",
        "west" : "r37/f15",
    ]));
    
}
