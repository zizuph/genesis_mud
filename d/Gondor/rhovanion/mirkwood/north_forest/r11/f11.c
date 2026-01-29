#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(61);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f12",
        "southwest" : "r10/f10",
        "south" : "r10/f11",
        "northwest" : "r12/f10",
        "east" : "r11/f12",
        "north" : "r12/f11",
        "northeast" : "r12/f12",
        "west" : "r11/f10",
    ]));
    
}
