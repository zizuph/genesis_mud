#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(58);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f24",
        "southwest" : "r13/f22",
        "south" : "r13/f23",
        "northwest" : "r15/f22",
        "east" : "r14/f24",
        "north" : "r15/f23",
        "northeast" : "r15/f24",
        "west" : "r14/f22",
    ]));
    
}
