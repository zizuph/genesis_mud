#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r17/f11",
        "southwest" : "r17/f09",
        "south" : "r17/f10",
        "northwest" : "r15/f09",
        "east" : "r16/f11",
        "north" : "r15/f10",
        "northeast" : "r15/f11",
        "west" : "r16/f09",
    ]));
    
}
