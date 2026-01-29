#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r15/f47",
        "southwest" : "r15/f45",
        "south" : "r15/f46",
        "northwest" : "r13/f45",
        "east" : "r14/f47",
        "north" : "r13/f46",
        "northeast" : "r13/f47",
        "west" : "r14/f45",
    ]));
    
}
