#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r22/f15",
        "southwest" : "r22/f13",
        "south" : "r22/f14",
        "northwest" : "r20/f13",
        "east" : "r21/f15",
        "north" : "r20/f14",
        "northeast" : "r20/f15",
        "west" : "r21/f13",
    ]));
    
}
