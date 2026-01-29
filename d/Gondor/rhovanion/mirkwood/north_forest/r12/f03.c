#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r11/f04",
        "southwest" : "r11/f02",
        "south" : "r11/f03",
        "northwest" : "r13/f02",
        "east" : "r12/f04",
        "north" : "r13/f03",
        "northeast" : "r13/f04",
        "west" : "r12/f02",
    ]));
    
}
