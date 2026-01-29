#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r13/f26",
        "southwest" : "r13/f24",
        "south" : "r13/f25",
        "northwest" : "r15/f24",
        "east" : "r14/f26",
        "north" : "r15/f25",
        "northeast" : "r15/f26",
        "west" : "r14/f24",
    ]));
    
}
