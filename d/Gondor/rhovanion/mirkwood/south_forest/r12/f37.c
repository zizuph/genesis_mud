#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r13/f38",
        "southwest" : "r13/f36",
        "south" : "r13/f37",
        "northwest" : "r11/f36",
        "east" : "r12/f38",
        "north" : "r11/f37",
        "northeast" : "r11/f38",
        "west" : "r12/f36",
    ]));
    
}
