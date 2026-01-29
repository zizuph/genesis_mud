#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r19/f22",
        "southwest" : "r19/f20",
        "south" : "r19/f21",
        "northwest" : "r17/f20",
        "east" : "r18/f22",
        "north" : "r17/f21",
        "northeast" : "r17/f22",
        "west" : "r18/f20",
    ]));
    
}
