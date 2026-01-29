#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f35",
        "southwest" : "r10/f33",
        "south" : "r10/f34",
        "northwest" : "r12/f33",
        "east" : "r11/f35",
        "north" : "r12/f34",
        "northeast" : "r12/f35",
        "west" : "r11/f33",
    ]));
    
}
