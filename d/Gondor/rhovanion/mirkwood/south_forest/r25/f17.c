#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r26/f18",
        "southwest" : "r26/f16",
        "south" : "r26/f17",
        "northwest" : "r24/f16",
        "east" : "r25/f18",
        "north" : "r24/f17",
        "northeast" : "r24/f18",
        "west" : "r25/f16",
    ]));
    
}
