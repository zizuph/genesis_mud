#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r10/f36",
        "southwest" : "r10/f34",
        "south" : "r10/f35",
        "northwest" : "r12/f34",
        "east" : "r11/f36",
        "north" : "r12/f35",
        "northeast" : "r12/f36",
        "west" : "r11/f34",
    ]));
    
}
