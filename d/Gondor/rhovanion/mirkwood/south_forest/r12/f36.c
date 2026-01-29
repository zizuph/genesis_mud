#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r13/f37",
        "southwest" : "r13/f35",
        "south" : "r13/f36",
        "northwest" : "r11/f35",
        "east" : "r12/f37",
        "north" : "r11/f36",
        "northeast" : "r11/f37",
        "west" : "r12/f35",
    ]));
    
}
