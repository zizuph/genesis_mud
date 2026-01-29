#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r15/f19",
        "southwest" : "r15/f17",
        "south" : "r15/f18",
        "northwest" : "r13/f17",
        "east" : "r14/f19",
        "north" : "r13/f18",
        "northeast" : "r13/f19",
        "west" : "r14/f17",
    ]));
    
}
