#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r14/f27",
        "southwest" : "r14/f25",
        "south" : "r14/f26",
        "northwest" : "r16/f25",
        "east" : "r15/f27",
        "north" : "r16/f26",
        "northeast" : "r16/f27",
        "west" : "r15/f25",
    ]));
    
}
