#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r11/f38",
        "southwest" : "r11/f36",
        "south" : "r11/f37",
        "northwest" : "r13/f36",
        "east" : "r12/f38",
        "north" : "r13/f37",
        "northeast" : "r13/f38",
        "west" : "r12/f36",
    ]));
    
}
