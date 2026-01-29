#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r10/f28",
        "southwest" : "r10/f26",
        "south" : "r10/f27",
        "northwest" : "r12/f26",
        "east" : "r11/f28",
        "north" : "r12/f27",
        "northeast" : "r12/f28",
        "west" : "r11/f26",
    ]));
    
}
