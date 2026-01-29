#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f23",
        "southwest" : "r11/f21",
        "south" : "r11/f22",
        "northwest" : "r13/f21",
        "east" : "r12/f23",
        "north" : "r13/f22",
        "northeast" : "r13/f23",
        "west" : "r12/f21",
    ]));
    
}
