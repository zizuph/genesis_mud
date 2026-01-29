#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r14/f23",
        "southwest" : "r14/f21",
        "south" : "r14/f22",
        "northwest" : "r12/f21",
        "east" : "r13/f23",
        "north" : "r12/f22",
        "northeast" : "r12/f23",
        "west" : "r13/f21",
    ]));
    
}
