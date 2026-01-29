#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r13/f27",
        "southwest" : "r13/f25",
        "south" : "r13/f26",
        "northwest" : "r11/f25",
        "east" : "r12/f27",
        "north" : "r11/f26",
        "northeast" : "r11/f27",
        "west" : "r12/f25",
    ]));
    
}
