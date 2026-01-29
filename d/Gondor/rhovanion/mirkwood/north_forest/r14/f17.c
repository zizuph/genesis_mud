#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f18",
        "southwest" : "r14/f16",
        "south" : "r13/f17",
        "northwest" : "r15/f16",
        "east" : "r14/f18",
        "north" : "r15/f17",
        "northeast" : "r15/f18",
        "west" : "r14/f16",
    ]));
    
}
