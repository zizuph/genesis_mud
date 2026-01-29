#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f46",
        "southwest" : "r14/f44",
        "south" : "r14/f45",
        "northwest" : "r12/f44",
        "east" : "r13/f46",
        "north" : "r12/f45",
        "northeast" : "r12/f46",
        "west" : "r13/f44",
    ]));
    
}
