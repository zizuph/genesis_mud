#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r19/f44",
        "southwest" : "r19/f42",
        "south" : "r19/f43",
        "northwest" : "r17/f42",
        "east" : "r18/f44",
        "north" : "r17/f43",
        "northeast" : "r17/f44",
        "west" : "r18/f42",
    ]));
    
}
