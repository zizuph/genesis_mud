#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r11/f28",
        "southwest" : "r11/f26",
        "south" : "r11/f27",
        "northwest" : "r13/f26",
        "east" : "r12/f28",
        "north" : "r13/f27",
        "northeast" : "r13/f28",
        "west" : "r12/f26",
    ]));
    
}
