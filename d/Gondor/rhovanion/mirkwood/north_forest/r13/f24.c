#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f25",
        "southwest" : "r12/f23",
        "south" : "r12/f24",
        "northwest" : "r14/f23",
        "east" : "r13/f25",
        "north" : "r14/f24",
        "northeast" : "r14/f25",
        "west" : "r13/f23",
    ]));
    
}
