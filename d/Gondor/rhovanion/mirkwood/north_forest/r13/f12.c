#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(44);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f13",
        "southwest" : "r12/f11",
        "south" : "r12/f12",
        "northwest" : "r14/f11",
        "east" : "r13/f13",
        "north" : "r14/f12",
        "northeast" : "r14/f13",
        "west" : "r13/f11",
    ]));
    
}
