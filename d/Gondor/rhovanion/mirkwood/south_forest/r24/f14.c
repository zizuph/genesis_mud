#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r25/f15",
        "southwest" : "r25/f13",
        "south" : "r25/f14",
        "northwest" : "r23/f13",
        "east" : "r24/f15",
        "north" : "r23/f14",
        "northeast" : "r23/f15",
        "west" : "r24/f13",
    ]));
    
}
