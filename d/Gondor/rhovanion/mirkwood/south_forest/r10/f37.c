#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f38",
        "southwest" : "r11/f36",
        "south" : "r11/f37",
        "northwest" : "r09/f36",
        "east" : "r10/f38",
        "north" : "r09/f37",
        "northeast" : "r09/f38",
        "west" : "r10/f36",
    ]));
    
}
