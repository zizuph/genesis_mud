#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r19/f43",
        "southwest" : "r19/f41",
        "south" : "r19/f42",
        "northwest" : "r17/f41",
        "east" : "r18/f43",
        "north" : "r17/f42",
        "northeast" : "r17/f43",
        "west" : "r18/f41",
    ]));
    
}
