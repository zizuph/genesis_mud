#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(4);
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
