#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r10/f37",
        "southwest" : "r10/f35",
        "south" : "r10/f36",
        "northwest" : "r12/f35",
        "east" : "r11/f37",
        "north" : "r12/f36",
        "northeast" : "r12/f37",
        "west" : "r11/f35",
    ]));
    
}
