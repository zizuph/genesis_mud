#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r24/f15",
        "southwest" : "r24/f13",
        "south" : "r24/f14",
        "northwest" : "r22/f13",
        "east" : "r23/f15",
        "north" : "r22/f14",
        "northeast" : "r22/f15",
        "west" : "r23/f13",
    ]));
    
}
