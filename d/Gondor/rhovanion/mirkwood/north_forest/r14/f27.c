#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f28",
        "southwest" : "r13/f26",
        "south" : "r13/f27",
        "northwest" : "r15/f26",
        "east" : "r14/f28",
        "north" : "r15/f27",
        "northeast" : "r15/f28",
        "west" : "r14/f26",
    ]));
    
}
