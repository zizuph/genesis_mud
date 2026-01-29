#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r19/f42",
        "southwest" : "r19/f40",
        "south" : "r19/f41",
        "northwest" : "r17/f40",
        "east" : "r18/f42",
        "north" : "r17/f41",
        "northeast" : "r17/f42",
        "west" : "r18/f40",
    ]));
    
}
