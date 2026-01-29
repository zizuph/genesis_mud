#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r16/f35",
        "southwest" : "r16/f33",
        "south" : "r16/f34",
        "northwest" : "r14/f33",
        "east" : "r15/f35",
        "north" : "r14/f34",
        "northeast" : "r14/f35",
        "west" : "r15/f33",
    ]));
    
}
