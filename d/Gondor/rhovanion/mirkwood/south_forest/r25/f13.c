#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r26/f14",
        "southwest" : "r26/f12",
        "south" : "r26/f13",
        "northwest" : "r24/f12",
        "east" : "r25/f14",
        "north" : "r24/f13",
        "northeast" : "r24/f14",
        "west" : "r25/f12",
    ]));
    
}
