#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f14",
        "southwest" : "r10/f12",
        "south" : "r10/f13",
        "northwest" : "r12/f12",
        "east" : "r11/f14",
        "north" : "r12/f13",
        "northeast" : "r12/f14",
        "west" : "r11/f12",
    ]));
    
}
