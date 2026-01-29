#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f21",
        "southwest" : "r14/f19",
        "south" : "r14/f20",
        "northwest" : "r16/f19",
        "east" : "r15/f21",
        "north" : "r16/f20",
        "northeast" : "r16/f21",
        "west" : "r15/f19",
    ]));
    
}
