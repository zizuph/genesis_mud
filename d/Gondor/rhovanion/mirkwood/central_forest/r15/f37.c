#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r14/f38",
        "southwest" : "r14/f36",
        "south" : "r14/f37",
        "northwest" : "r16/f36",
        "east" : "r15/f38",
        "north" : "r16/f37",
        "northeast" : "r16/f38",
        "west" : "r15/f36",
    ]));
    
}
