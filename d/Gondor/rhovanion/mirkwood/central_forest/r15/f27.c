#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r14/f28",
        "southwest" : "r14/f26",
        "south" : "r14/f27",
        "northwest" : "r16/f26",
        "east" : "r15/f28",
        "north" : "r16/f27",
        "northeast" : "r16/f28",
        "west" : "r15/f26",
    ]));
    
}
