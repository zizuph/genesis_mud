#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(33);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f38",
        "southwest" : "r09/f36",
        "south" : "r09/f37",
        "northwest" : "r11/f36",
        "east" : "r10/f38",
        "north" : "r11/f37",
        "northeast" : "r11/f38",
        "west" : "r10/f36",
    ]));
    
}
