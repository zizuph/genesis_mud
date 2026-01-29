#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(14);
    add_mirkwood_exits(([
        "southeast" : "r15/f27",
        "southwest" : "r15/f25",
        "south" : "r15/f26",
        "northwest" : "r13/f25",
        "east" : "r14/f27",
        "north" : "r13/f26",
        "northeast" : "r13/f27",
        "west" : "r14/f25",
    ]));
    
}
