#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r10/f26",
        "southwest" : "r10/f24",
        "south" : "r10/f25",
        "northwest" : "r12/f24",
        "east" : "r11/f26",
        "north" : "r12/f25",
        "northeast" : "r12/f26",
        "west" : "r11/f24",
    ]));
    
}
