#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r14/f22",
        "southwest" : "r14/f20",
        "south" : "r14/f21",
        "northwest" : "r12/f20",
        "east" : "r13/f22",
        "north" : "r12/f21",
        "northeast" : "r12/f22",
        "west" : "r13/f20",
    ]));
    
}
