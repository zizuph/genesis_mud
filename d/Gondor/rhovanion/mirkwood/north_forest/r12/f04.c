#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r11/f05",
        "southwest" : "r11/f03",
        "south" : "r11/f04",
        "northwest" : "r13/f03",
        "east" : "r12/f05",
        "north" : "r13/f04",
        "northeast" : "r13/f05",
        "west" : "r12/f03",
    ]));
    
}
