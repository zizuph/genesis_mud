#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r13/f39",
        "southwest" : "r13/f37",
        "south" : "r13/f38",
        "northwest" : "r15/f37",
        "east" : "r14/f39",
        "north" : "r15/f38",
        "northeast" : "r15/f39",
        "west" : "r14/f37",
    ]));
    
}
