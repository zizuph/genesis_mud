#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r25/f19",
        "southwest" : "r25/f17",
        "south" : "r25/f18",
        "northwest" : "r23/f17",
        "east" : "r24/f19",
        "north" : "r23/f18",
        "northeast" : "r23/f19",
        "west" : "r24/f17",
    ]));
    
}
