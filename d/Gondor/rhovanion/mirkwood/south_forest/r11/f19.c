#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r12/f20",
        "southwest" : "r12/f18",
        "south" : "r12/f19",
        "northwest" : "r10/f18",
        "east" : "r11/f20",
        "north" : "r10/f19",
        "northeast" : "r10/f20",
        "west" : "r11/f18",
    ]));
    
}
