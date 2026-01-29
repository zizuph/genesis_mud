#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r11/f26",
        "southwest" : "r11/f24",
        "south" : "r11/f25",
        "northwest" : "r13/f24",
        "east" : "r12/f26",
        "north" : "r13/f25",
        "northeast" : "r13/f26",
        "west" : "r12/f24",
    ]));
    
}
