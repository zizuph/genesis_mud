#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(31);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f36",
        "southwest" : "r09/f34",
        "south" : "r09/f35",
        "northwest" : "r11/f34",
        "east" : "r10/f36",
        "north" : "r11/f35",
        "northeast" : "r11/f36",
        "west" : "r10/f34",
    ]));
    
}
