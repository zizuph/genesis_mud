#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r26/f15",
        "southwest" : "r26/f13",
        "south" : "r26/f14",
        "northwest" : "r24/f13",
        "east" : "r25/f15",
        "north" : "r24/f14",
        "northeast" : "r24/f15",
        "west" : "r25/f13",
    ]));
    
}
