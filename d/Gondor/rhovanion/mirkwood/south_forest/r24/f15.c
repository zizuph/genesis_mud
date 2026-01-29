#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r25/f16",
        "southwest" : "r25/f14",
        "south" : "r25/f15",
        "northwest" : "r23/f14",
        "east" : "r24/f16",
        "north" : "r23/f15",
        "northeast" : "r23/f16",
        "west" : "r24/f14",
    ]));
    
}
