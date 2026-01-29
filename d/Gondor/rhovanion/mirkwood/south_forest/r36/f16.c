#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r37/f17",
        "southwest" : "r37/f15",
        "south" : "r37/f16",
        "northwest" : "r35/f15",
        "east" : "r36/f17",
        "north" : "r35/f16",
        "northeast" : "r35/f17",
        "west" : "r36/f15",
    ]));
    
}
