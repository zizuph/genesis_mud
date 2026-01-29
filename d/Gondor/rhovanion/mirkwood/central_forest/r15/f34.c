#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r14/f35",
        "southwest" : "r14/f33",
        "south" : "r14/f34",
        "northwest" : "r16/f33",
        "east" : "r15/f35",
        "north" : "r16/f34",
        "northeast" : "r16/f35",
        "west" : "r15/f33",
    ]));
    
}
