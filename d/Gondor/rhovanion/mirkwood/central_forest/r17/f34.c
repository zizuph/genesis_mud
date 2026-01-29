#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f35",
        "southwest" : "r16/f33",
        "south" : "r16/f34",
        "northwest" : "r18/f33",
        "east" : "r17/f35",
        "north" : "r18/f34",
        "northeast" : "r18/f35",
        "west" : "r17/f33",
    ]));
    
}
