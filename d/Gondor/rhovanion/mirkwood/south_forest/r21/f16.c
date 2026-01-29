#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r22/f17",
        "southwest" : "r22/f15",
        "south" : "r22/f16",
        "northwest" : "r20/f15",
        "east" : "r21/f17",
        "north" : "r20/f16",
        "northeast" : "r20/f17",
        "west" : "r21/f15",
    ]));
    
}
