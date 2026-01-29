#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r24/f23",
        "southwest" : "r24/f21",
        "south" : "r24/f22",
        "northwest" : "r22/f21",
        "east" : "r23/f23",
        "north" : "r22/f22",
        "northeast" : "r22/f23",
        "west" : "r23/f21",
    ]));
    
}
