#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r24/f16",
        "southwest" : "r24/f14",
        "south" : "r24/f15",
        "northwest" : "r22/f14",
        "east" : "r23/f16",
        "north" : "r22/f15",
        "northeast" : "r22/f16",
        "west" : "r23/f14",
    ]));
    
}
