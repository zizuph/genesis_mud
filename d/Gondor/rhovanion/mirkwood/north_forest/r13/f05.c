#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r12/f06",
        "southwest" : "r12/f04",
        "south" : "r12/f05",
        "northwest" : "r14/f04",
        "east" : "r13/f06",
        "north" : "r14/f05",
        "northeast" : "r14/f06",
        "west" : "r13/f04",
    ]));
    
}
