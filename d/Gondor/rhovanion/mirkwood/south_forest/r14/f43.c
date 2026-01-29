#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r15/f44",
        "southwest" : "r15/f42",
        "south" : "r15/f43",
        "northwest" : "r13/f42",
        "east" : "r14/f44",
        "north" : "r13/f43",
        "northeast" : "r13/f44",
        "west" : "r14/f42",
    ]));
    
}
