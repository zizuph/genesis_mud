#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r14/f45",
        "southwest" : "r14/f43",
        "south" : "r14/f44",
        "northwest" : "r12/f43",
        "east" : "r13/f45",
        "north" : "r12/f44",
        "northeast" : "r12/f45",
        "west" : "r13/f43",
    ]));
    
}
