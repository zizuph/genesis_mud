#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f12",
        "southwest" : "r12/f10",
        "south" : "r12/f11",
        "northwest" : "r14/f10",
        "east" : "r13/f12",
        "north" : "r14/f11",
        "northeast" : "r14/f12",
        "west" : "r13/f10",
    ]));
    
}
