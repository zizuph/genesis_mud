#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r25/f28",
        "southwest" : "r25/f26",
        "south" : "r25/f27",
        "northwest" : "r23/f26",
        "east" : "r24/f28",
        "north" : "r23/f27",
        "northeast" : "r23/f28",
        "west" : "r24/f26",
    ]));
    
}
