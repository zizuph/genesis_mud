#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(69);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r14/f21",
        "southwest" : "r14/f20",
        "south" : "r14/f20",
        "northwest" : "r16/f19",
        "east" : "r15/f21",
        "north" : "r16/f20",
        "northeast" : "r16/f21",
        "west" : "r15/f19",
    ]));
    
}
