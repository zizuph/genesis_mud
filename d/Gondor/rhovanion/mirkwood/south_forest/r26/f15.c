#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r27/f16",
        "southwest" : "r27/f14",
        "south" : "r27/f15",
        "northwest" : "r25/f14",
        "east" : "r26/f16",
        "north" : "r25/f15",
        "northeast" : "r25/f16",
        "west" : "r26/f14",
    ]));
    
}
