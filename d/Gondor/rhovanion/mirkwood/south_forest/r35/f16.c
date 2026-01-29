#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r36/f17",
        "southwest" : "r36/f15",
        "south" : "r36/f16",
        "northwest" : "r34/f15",
        "east" : "r35/f17",
        "north" : "r34/f16",
        "northeast" : "r34/f17",
        "west" : "r35/f15",
    ]));
    
}
