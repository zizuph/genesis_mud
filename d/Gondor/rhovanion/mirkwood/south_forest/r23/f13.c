#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r24/f14",
        "southwest" : "r24/f12",
        "south" : "r24/f13",
        "northwest" : "r22/f12",
        "east" : "r23/f14",
        "north" : "r22/f13",
        "northeast" : "r22/f14",
        "west" : "r23/f12",
    ]));
    
}
