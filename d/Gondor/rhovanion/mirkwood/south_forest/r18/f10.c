#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r19/f11",
        "southwest" : "r19/f09",
        "south" : "r19/f10",
        "northwest" : "r17/f09",
        "east" : "r18/f11",
        "north" : "r17/f10",
        "northeast" : "r17/f11",
        "west" : "r18/f09",
    ]));
    
}
