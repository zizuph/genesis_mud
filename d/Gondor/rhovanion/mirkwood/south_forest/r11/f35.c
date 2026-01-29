#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f36",
        "southwest" : "r12/f34",
        "south" : "r12/f35",
        "northwest" : "r10/f34",
        "east" : "r11/f36",
        "north" : "r10/f35",
        "northeast" : "r10/f36",
        "west" : "r11/f34",
    ]));
    
}
