#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r13/f27",
        "southwest" : "r13/f25",
        "south" : "r13/f26",
        "northwest" : "r15/f25",
        "east" : "r14/f27",
        "north" : "r15/f26",
        "northeast" : "r15/f27",
        "west" : "r14/f25",
    ]));
    
}
