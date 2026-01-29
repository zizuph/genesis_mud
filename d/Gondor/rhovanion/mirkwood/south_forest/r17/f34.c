#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r18/f35",
        "southwest" : "r18/f33",
        "south" : "r18/f34",
        "northwest" : "r16/f33",
        "east" : "r17/f35",
        "north" : "r16/f34",
        "northeast" : "r16/f35",
        "west" : "r17/f33",
    ]));
    
}
