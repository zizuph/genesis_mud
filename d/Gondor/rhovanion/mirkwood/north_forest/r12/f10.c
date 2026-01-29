#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(48);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r11/f11",
        "southwest" : "r11/f09",
        "south" : "r11/f10",
        "northwest" : "r13/f09",
        "east" : "r12/f11",
        "north" : "r13/f10",
        "northeast" : "r13/f11",
        "west" : "r12/f09",
    ]));
    
}
