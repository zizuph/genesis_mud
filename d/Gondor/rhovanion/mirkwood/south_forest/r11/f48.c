#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r12/f49",
        "southwest" : "r12/f47",
        "south" : "r12/f48",
        "northwest" : "r10/f47",
        "east" : "r11/f49",
        "north" : "r10/f48",
        "northeast" : "r10/f49",
        "west" : "r11/f47",
    ]));
    
}
