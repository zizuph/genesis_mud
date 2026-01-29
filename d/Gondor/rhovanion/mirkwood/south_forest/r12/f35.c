#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r13/f36",
        "southwest" : "r13/f34",
        "south" : "r13/f35",
        "northwest" : "r11/f34",
        "east" : "r12/f36",
        "north" : "r11/f35",
        "northeast" : "r11/f36",
        "west" : "r12/f34",
    ]));
    
}
