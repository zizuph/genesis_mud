#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(32);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f37",
        "southwest" : "r09/f35",
        "south" : "r09/f36",
        "northwest" : "r11/f35",
        "east" : "r10/f37",
        "north" : "r11/f36",
        "northeast" : "r11/f37",
        "west" : "r10/f35",
    ]));
    
}
