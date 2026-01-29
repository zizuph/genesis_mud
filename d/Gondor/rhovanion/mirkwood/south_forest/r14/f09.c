#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r15/f10",
        "southwest" : "r15/f08",
        "south" : "r15/f09",
        "northwest" : "r13/f08",
        "east" : "r14/f10",
        "north" : "r13/f09",
        "northeast" : "r13/f10",
        "west" : "r14/f08",
    ]));
    
}
