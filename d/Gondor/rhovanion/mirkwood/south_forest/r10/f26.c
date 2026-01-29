#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f27",
        "southwest" : "r11/f25",
        "south" : "r11/f26",
        "northwest" : "r09/f25",
        "east" : "r10/f27",
        "north" : "r09/f26",
        "northeast" : "r09/f27",
        "west" : "r10/f25",
    ]));
    
}
