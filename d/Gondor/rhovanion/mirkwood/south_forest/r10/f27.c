#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f28",
        "southwest" : "r11/f26",
        "south" : "r11/f27",
        "northwest" : "r09/f26",
        "east" : "r10/f28",
        "north" : "r09/f27",
        "northeast" : "r09/f28",
        "west" : "r10/f26",
    ]));
    
}
