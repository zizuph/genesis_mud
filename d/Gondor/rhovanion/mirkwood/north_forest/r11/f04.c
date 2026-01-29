#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r10/f05",
        "southwest" : "r10/f03",
        "south" : "r10/f04",
        "northwest" : "r12/f03",
        "east" : "r11/f05",
        "north" : "r12/f04",
        "northeast" : "r12/f05",
        "west" : "r11/f03",
    ]));
    
}
