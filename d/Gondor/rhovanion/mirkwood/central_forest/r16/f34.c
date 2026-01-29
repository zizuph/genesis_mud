#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f35",
        "southwest" : "r15/f33",
        "south" : "r15/f34",
        "northwest" : "r17/f33",
        "east" : "r16/f35",
        "north" : "r17/f34",
        "northeast" : "r17/f35",
        "west" : "r16/f33",
    ]));
    
}
