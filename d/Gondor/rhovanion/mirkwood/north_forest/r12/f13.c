#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(7);
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
