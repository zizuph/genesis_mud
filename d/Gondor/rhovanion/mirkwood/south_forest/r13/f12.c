#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r14/f13",
        "southwest" : "r14/f11",
        "south" : "r14/f12",
        "northwest" : "r12/f11",
        "east" : "r13/f13",
        "north" : "r12/f12",
        "northeast" : "r12/f13",
        "west" : "r13/f11",
    ]));
    
}
