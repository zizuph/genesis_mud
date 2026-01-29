#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f19",
        "southwest" : "r13/f17",
        "south" : "r13/f18",
        "northwest" : "r15/f17",
        "east" : "r14/f19",
        "north" : "r15/f18",
        "northeast" : "r15/f19",
        "west" : "r14/f17",
    ]));
    
}
