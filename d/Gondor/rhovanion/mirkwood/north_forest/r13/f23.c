#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r12/f24",
        "southwest" : "r12/f22",
        "south" : "r12/f23",
        "northwest" : "r14/f22",
        "east" : "r13/f24",
        "north" : "r14/f23",
        "northeast" : "r14/f24",
        "west" : "r13/f22",
    ]));
    
}
