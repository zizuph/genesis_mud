#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r15/f21",
        "southwest" : "r15/f19",
        "south" : "r15/f20",
        "northwest" : "r13/f19",
        "east" : "r14/f21",
        "north" : "r13/f20",
        "northeast" : "r13/f21",
        "west" : "r14/f19",
    ]));
    
}
