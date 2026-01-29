#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r27/f17",
        "southwest" : "r27/f15",
        "south" : "r27/f16",
        "northwest" : "r25/f15",
        "east" : "r26/f17",
        "north" : "r25/f16",
        "northeast" : "r25/f17",
        "west" : "r26/f15",
    ]));
    
}
