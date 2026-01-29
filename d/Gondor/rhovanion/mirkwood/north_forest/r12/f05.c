#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(45);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r11/f06",
        "southwest" : "r11/f04",
        "south" : "r11/f05",
        "northwest" : "r13/f04",
        "east" : "r12/f06",
        "north" : "r13/f05",
        "northeast" : "r13/f06",
        "west" : "r12/f04",
    ]));
    
}
