#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f37",
        "southwest" : "r12/f35",
        "south" : "r12/f36",
        "northwest" : "r10/f35",
        "east" : "r11/f37",
        "north" : "r10/f36",
        "northeast" : "r10/f37",
        "west" : "r11/f35",
    ]));
    
}
