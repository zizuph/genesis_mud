#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f37",
        "southwest" : "r11/f35",
        "south" : "r11/f36",
        "northwest" : "r13/f35",
        "east" : "r12/f37",
        "north" : "r13/f36",
        "northeast" : "r13/f37",
        "west" : "r12/f35",
    ]));
    
}
