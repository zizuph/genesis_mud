#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(58);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f35",
        "southwest" : "r09/f33",
        "south" : "r09/f34",
        "northwest" : "r11/f33",
        "east" : "r10/f35",
        "north" : "r11/f34",
        "northeast" : "r11/f35",
        "west" : "r10/f33",
    ]));
    
}
