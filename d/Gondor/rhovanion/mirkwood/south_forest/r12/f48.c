#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r13/f49",
        "southwest" : "r13/f47",
        "south" : "r13/f48",
        "northwest" : "r11/f47",
        "east" : "r12/f49",
        "north" : "r11/f48",
        "northeast" : "r11/f49",
        "west" : "r12/f47",
    ]));
    
}
