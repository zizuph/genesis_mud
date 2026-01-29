#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(53);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r10/f25",
        "southwest" : "r10/f24",
        "south" : "r10/f24",
        "northwest" : "r12/f23",
        "east" : "r11/f25",
        "north" : "r12/f24",
        "northeast" : "r12/f25",
        "west" : "r11/f23",
    ]));
    
}
