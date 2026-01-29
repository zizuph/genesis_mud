#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r25/f22",
        "southwest" : "r25/f20",
        "south" : "r25/f21",
        "northwest" : "r23/f20",
        "east" : "r24/f22",
        "north" : "r23/f21",
        "northeast" : "r23/f22",
        "west" : "r24/f20",
    ]));
    
}
