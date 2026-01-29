#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r14/f10",
        "southwest" : "r14/f08",
        "south" : "r14/f09",
        "northwest" : "r12/f08",
        "east" : "r13/f10",
        "north" : "r12/f09",
        "northeast" : "r12/f10",
        "west" : "r13/f08",
    ]));
    
}
