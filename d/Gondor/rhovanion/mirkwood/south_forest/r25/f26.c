#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r26/f27",
        "southwest" : "r26/f25",
        "south" : "r26/f26",
        "northwest" : "r24/f25",
        "east" : "r25/f27",
        "north" : "r24/f26",
        "northeast" : "r24/f27",
        "west" : "r25/f25",
    ]));
    
}
