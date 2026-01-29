#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r18/f11",
        "southwest" : "r18/f09",
        "south" : "r18/f10",
        "northwest" : "r16/f09",
        "east" : "r17/f11",
        "north" : "r16/f10",
        "northeast" : "r16/f11",
        "west" : "r17/f09",
    ]));
    
}
