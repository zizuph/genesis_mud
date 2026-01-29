#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(31);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f11",
        "southwest" : "r12/f09",
        "south" : "r12/f10",
        "northwest" : "r14/f09",
        "east" : "r13/f11",
        "north" : "r14/f10",
        "northeast" : "r14/f11",
        "west" : "r13/f09",
    ]));
    
}
