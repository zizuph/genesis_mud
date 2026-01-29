#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r10/f03",
        "southwest" : "r10/f01",
        "south" : "r10/f02",
        "northwest" : "r12/f01",
        "east" : "r11/f03",
        "north" : "r12/f02",
        "northeast" : "r12/f03",
        "west" : "r11/f01",
    ]));
    
}
