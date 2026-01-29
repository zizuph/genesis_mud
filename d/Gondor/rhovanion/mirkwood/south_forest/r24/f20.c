#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r25/f21",
        "southwest" : "r25/f19",
        "south" : "r25/f20",
        "northwest" : "r23/f19",
        "east" : "r24/f21",
        "north" : "r23/f20",
        "northeast" : "r23/f21",
        "west" : "r24/f19",
    ]));
    
}
