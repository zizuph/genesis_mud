#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r15/f11",
        "southwest" : "r15/f09",
        "south" : "r15/f10",
        "northwest" : "r17/f09",
        "east" : "r16/f11",
        "north" : "r17/f10",
        "northeast" : "r17/f11",
        "west" : "r16/f09",
    ]));
    
}
