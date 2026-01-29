#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r12/f47",
        "southwest" : "r12/f45",
        "south" : "r12/f46",
        "northwest" : "r10/f45",
        "east" : "r11/f47",
        "north" : "r10/f46",
        "northeast" : "r10/f47",
        "west" : "r11/f45",
    ]));
    
}
