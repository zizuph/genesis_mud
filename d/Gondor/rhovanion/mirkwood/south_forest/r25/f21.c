#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r26/f22",
        "southwest" : "r26/f20",
        "south" : "r26/f21",
        "northwest" : "r24/f20",
        "east" : "r25/f22",
        "north" : "r24/f21",
        "northeast" : "r24/f22",
        "west" : "r25/f20",
    ]));
    
}
