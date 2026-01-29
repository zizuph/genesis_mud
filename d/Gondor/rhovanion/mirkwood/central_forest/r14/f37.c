#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f38",
        "southwest" : "r13/f36",
        "south" : "r13/f37",
        "northwest" : "r15/f36",
        "east" : "r14/f38",
        "north" : "r15/f37",
        "northeast" : "r15/f38",
        "west" : "r14/f36",
    ]));
    
}
