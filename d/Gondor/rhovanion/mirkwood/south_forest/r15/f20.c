#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r16/f21",
        "southwest" : "r16/f19",
        "south" : "r16/f20",
        "northwest" : "r14/f19",
        "east" : "r15/f21",
        "north" : "r14/f20",
        "northeast" : "r14/f21",
        "west" : "r15/f19",
    ]));
    
}
