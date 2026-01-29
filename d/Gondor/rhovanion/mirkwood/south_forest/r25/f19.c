#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r26/f20",
        "southwest" : "r26/f18",
        "south" : "r26/f19",
        "northwest" : "r24/f18",
        "east" : "r25/f20",
        "north" : "r24/f19",
        "northeast" : "r24/f20",
        "west" : "r25/f18",
    ]));
    
}
