#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r16/f36",
        "southwest" : "r16/f34",
        "south" : "r16/f35",
        "northwest" : "r18/f34",
        "east" : "r17/f36",
        "north" : "r18/f35",
        "northeast" : "r18/f36",
        "west" : "r17/f34",
    ]));
    
}
