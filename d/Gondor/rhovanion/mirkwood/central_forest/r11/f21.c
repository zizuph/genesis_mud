#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f22",
        "southwest" : "r10/f20",
        "south" : "r10/f21",
        "northwest" : "r12/f20",
        "east" : "r11/f22",
        "north" : "r12/f21",
        "northeast" : "r11/f22",
        "west" : "r11/f20",
    ]));
    
}
