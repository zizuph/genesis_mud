#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(88);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r13/f18",
        "southwest" : "r13/f16",
        "south" : "r13/f17",
        "northwest" : "r15/f16",
        "east" : "r14/f18",
        "north" : "r15/f17",
        "northeast" : "r15/f18",
        "west" : "r14/f16",
    ]));
    
}
