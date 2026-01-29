#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r10/f04",
        "southwest" : "r10/f02",
        "south" : "r10/f03",
        "northwest" : "r12/f02",
        "east" : "r11/f04",
        "north" : "r12/f03",
        "northeast" : "r12/f04",
        "west" : "r11/f02",
    ]));
    
}
