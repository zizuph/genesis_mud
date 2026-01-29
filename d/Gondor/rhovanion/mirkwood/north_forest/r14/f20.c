#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f21",
        "southwest" : "r13/f19",
        "south" : "r13/f20",
        "northwest" : "r15/f19",
        "east" : "r14/f21",
        "north" : "r15/f20",
        "northeast" : "r15/f21",
        "west" : "r14/f19",
    ]));
    
}
