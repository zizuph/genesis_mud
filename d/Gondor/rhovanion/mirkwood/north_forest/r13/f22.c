#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f23",
        "southwest" : "r12/f21",
        "south" : "r12/f22",
        "northwest" : "r14/f21",
        "east" : "r13/f23",
        "north" : "r14/f22",
        "northeast" : "r14/f23",
        "west" : "r13/f21",
    ]));
    
}
