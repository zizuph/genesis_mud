#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r26/f17",
        "southwest" : "r26/f15",
        "south" : "r26/f16",
        "northwest" : "r24/f15",
        "east" : "r25/f17",
        "north" : "r24/f16",
        "northeast" : "r24/f17",
        "west" : "r25/f15",
    ]));
    
}
