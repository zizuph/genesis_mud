#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r13/f20",
        "southwest" : "r13/f18",
        "south" : "r13/f19",
        "northwest" : "r11/f18",
        "east" : "r12/f20",
        "north" : "r11/f19",
        "northeast" : "r11/f20",
        "west" : "r12/f18",
    ]));
    
}
