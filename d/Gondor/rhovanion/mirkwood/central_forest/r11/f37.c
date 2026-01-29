#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f38",
        "southwest" : "r10/f36",
        "south" : "r10/f37",
        "northwest" : "r12/f36",
        "east" : "r11/f38",
        "north" : "r12/f37",
        "northeast" : "r12/f38",
        "west" : "r11/f36",
    ]));
    
}
