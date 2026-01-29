#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r13/f10",
        "southwest" : "r13/f08",
        "south" : "r13/f09",
        "northwest" : "r15/f08",
        "east" : "r14/f10",
        "north" : "r15/f09",
        "northeast" : "r15/f10",
        "west" : "r14/f08",
    ]));
    
}
