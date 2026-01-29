#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(34);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f21",
        "southwest" : "r11/f19",
        "south" : "r10/f20",
        "northwest" : "r12/f19",
        "east" : "r11/f21",
        "north" : "r12/f20",
        "northeast" : "r12/f21",
        "west" : "r11/f19",
    ]));
    
}
