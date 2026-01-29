#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f13",
        "southwest" : "r11/f11",
        "south" : "r11/f12",
        "northwest" : "r13/f11",
        "east" : "r12/f13",
        "north" : "r13/f12",
        "northeast" : "r13/f13",
        "west" : "r12/f11",
    ]));
    
}
