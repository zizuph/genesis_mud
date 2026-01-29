#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f38",
        "southwest" : "r12/f36",
        "south" : "r12/f37",
        "northwest" : "r10/f36",
        "east" : "r11/f38",
        "north" : "r10/f37",
        "northeast" : "r10/f38",
        "west" : "r11/f36",
    ]));
    
}
