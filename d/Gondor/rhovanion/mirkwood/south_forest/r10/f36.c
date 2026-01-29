#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f37",
        "southwest" : "r11/f35",
        "south" : "r11/f36",
        "northwest" : "r09/f35",
        "east" : "r10/f37",
        "north" : "r09/f36",
        "northeast" : "r09/f37",
        "west" : "r10/f35",
    ]));
    
}
