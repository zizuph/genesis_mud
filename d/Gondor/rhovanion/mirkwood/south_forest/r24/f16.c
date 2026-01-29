#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r25/f17",
        "southwest" : "r25/f15",
        "south" : "r25/f16",
        "northwest" : "r23/f15",
        "east" : "r24/f17",
        "north" : "r23/f16",
        "northeast" : "r23/f17",
        "west" : "r24/f15",
    ]));
    
}
