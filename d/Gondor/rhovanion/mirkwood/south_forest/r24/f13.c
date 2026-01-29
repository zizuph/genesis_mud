#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r25/f14",
        "southwest" : "r25/f12",
        "south" : "r25/f13",
        "northwest" : "r23/f12",
        "east" : "r24/f14",
        "north" : "r23/f13",
        "northeast" : "r23/f14",
        "west" : "r24/f12",
    ]));
    
}
