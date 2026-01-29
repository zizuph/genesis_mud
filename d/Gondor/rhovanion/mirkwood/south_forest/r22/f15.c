#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r23/f16",
        "southwest" : "r23/f14",
        "south" : "r23/f15",
        "northwest" : "r21/f14",
        "east" : "r22/f16",
        "north" : "r21/f15",
        "northeast" : "r21/f16",
        "west" : "r22/f14",
    ]));
    
}
