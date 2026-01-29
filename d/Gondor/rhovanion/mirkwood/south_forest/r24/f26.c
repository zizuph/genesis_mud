#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r25/f27",
        "southwest" : "r25/f25",
        "south" : "r25/f26",
        "northwest" : "r23/f25",
        "east" : "r24/f27",
        "north" : "r23/f26",
        "northeast" : "r23/f27",
        "west" : "r24/f25",
    ]));
    
}
