#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(35);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f10",
        "southwest" : "r12/f08",
        "south" : "r12/f09",
        "northwest" : "r14/f08",
        "east" : "r13/f10",
        "north" : "r14/f09",
        "northeast" : "r14/f10",
        "west" : "r13/f08",
    ]));
    
}
