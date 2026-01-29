#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r26/f21",
        "southwest" : "r26/f19",
        "south" : "r26/f20",
        "northwest" : "r24/f19",
        "east" : "r25/f21",
        "north" : "r24/f20",
        "northeast" : "r24/f21",
        "west" : "r25/f19",
    ]));
    
}
