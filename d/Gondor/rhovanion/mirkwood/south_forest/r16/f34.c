#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r17/f35",
        "southwest" : "r17/f33",
        "south" : "r17/f34",
        "northwest" : "r15/f33",
        "east" : "r16/f35",
        "north" : "r15/f34",
        "northeast" : "r15/f35",
        "west" : "r16/f33",
    ]));
    
}
