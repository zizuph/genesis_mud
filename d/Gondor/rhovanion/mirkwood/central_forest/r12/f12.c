#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r11/f13",
        "southwest" : "r11/f11",
        "south" : "r11/f12",
        "northwest" : "r13/f11",
        "east" : "r12/f13",
        "north" : "r13/f12",
        "northeast" : "r13/f13",
        "west" : "r12/f11",
    ]));
    
}
