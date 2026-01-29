#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(32);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f22",
        "southwest" : "r10/f20",
        "south" : "r10/f21",
        "northwest" : "r12/f20",
        "east" : "r11/f22",
        "north" : "r12/f21",
        "northeast" : "r12/f22",
        "west" : "r11/f20",
    ]));
    
}
