#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f12",
        "southwest" : "r13/f10",
        "south" : "r13/f11",
        "northwest" : "r11/f10",
        "east" : "r12/f12",
        "north" : "r11/f11",
        "northeast" : "r11/f12",
        "west" : "r12/f10",
    ]));
    
}
