#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f39",
        "southwest" : "r14/f37",
        "south" : "r14/f38",
        "northwest" : "r16/f37",
        "east" : "r15/f39",
        "north" : "r16/f38",
        "northeast" : "r16/f39",
        "west" : "r15/f37",
    ]));
    
}
