#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r12/f05",
        "southwest" : "r12/f03",
        "south" : "r12/f04",
        "northwest" : "r14/f03",
        "east" : "r13/f05",
        "north" : "r14/f04",
        "northeast" : "r14/f05",
        "west" : "r13/f03",
    ]));
    
}
