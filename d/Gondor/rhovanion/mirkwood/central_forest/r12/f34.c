#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f35",
        "southwest" : "r11/f33",
        "south" : "r11/f34",
        "northwest" : "r13/f33",
        "east" : "r12/f35",
        "north" : "r13/f34",
        "northeast" : "r13/f35",
        "west" : "r12/f33",
    ]));
    
}
