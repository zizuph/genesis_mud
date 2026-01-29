#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r26/f23",
        "southwest" : "r26/f21",
        "south" : "r26/f22",
        "northwest" : "r24/f21",
        "east" : "r25/f23",
        "north" : "r24/f22",
        "northeast" : "r24/f23",
        "west" : "r25/f21",
    ]));
    
}
