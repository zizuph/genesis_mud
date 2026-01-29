#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r10/f11",
        "southwest" : "r10/f09",
        "south" : "r10/f10",
        "northwest" : "r12/f09",
        "east" : "r11/f11",
        "north" : "r12/f10",
        "northeast" : "r12/f11",
        "west" : "r11/f09",
    ]));
    
}
