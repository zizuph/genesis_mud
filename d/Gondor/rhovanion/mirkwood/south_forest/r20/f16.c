#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r20/f17",
        "southwest" : "r20/f15",
        "south" : "r20/f16",
        "northwest" : "r19/f15",
        "east" : "r20/f17",
        "north" : "r19/f16",
        "northeast" : "r19/f17",
        "west" : "r20/f15",
    ]));
    
}
