#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r26/f16",
        "southwest" : "r26/f14",
        "south" : "r26/f15",
        "northwest" : "r24/f14",
        "east" : "r25/f16",
        "north" : "r24/f15",
        "northeast" : "r24/f16",
        "west" : "r25/f14",
    ]));
    
}
