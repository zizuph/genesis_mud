#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f11",
        "southwest" : "r16/f09",
        "south" : "r16/f10",
        "northwest" : "r14/f09",
        "east" : "r15/f11",
        "north" : "r14/f10",
        "northeast" : "r14/f11",
        "west" : "r15/f09",
    ]));
    
}
