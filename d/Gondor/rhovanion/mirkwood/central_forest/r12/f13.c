#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f14",
        "southwest" : "r11/f12",
        "south" : "r11/f13",
        "northwest" : "r13/f12",
        "east" : "r12/f14",
        "north" : "r13/f13",
        "northeast" : "r13/f14",
        "west" : "r12/f12",
    ]));
    
}
