#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(35);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r10/f06",
        "southwest" : "r10/f04",
        "south" : "r10/f05",
        "northwest" : "r12/f04",
        "east" : "r11/f06",
        "north" : "r12/f05",
        "northeast" : "r12/f06",
        "west" : "r11/f04",
    ]));
    
}
