#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(34);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f25",
        "southwest" : "r13/f23",
        "south" : "r13/f24",
        "northwest" : "r15/f23",
        "east" : "r14/f25",
        "north" : "r15/f24",
        "northeast" : "r15/f25",
        "west" : "r14/f23",
    ]));
    
}
