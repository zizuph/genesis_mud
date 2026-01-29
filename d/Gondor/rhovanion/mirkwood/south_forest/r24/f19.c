#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r25/f20",
        "southwest" : "r25/f18",
        "south" : "r25/f19",
        "northwest" : "r23/f18",
        "east" : "r24/f20",
        "north" : "r23/f19",
        "northeast" : "r23/f20",
        "west" : "r24/f18",
    ]));
    
}
