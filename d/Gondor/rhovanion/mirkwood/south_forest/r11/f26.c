#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f27",
        "southwest" : "r12/f25",
        "south" : "r12/f26",
        "northwest" : "r10/f25",
        "east" : "r11/f27",
        "north" : "r10/f26",
        "northeast" : "r10/f27",
        "west" : "r11/f25",
    ]));
    
}
