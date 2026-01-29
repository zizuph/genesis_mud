#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f26",
        "southwest" : "r11/f24",
        "south" : "r11/f25",
        "northwest" : "r09/f24",
        "east" : "r10/f26",
        "north" : "r09/f25",
        "northeast" : "r09/f26",
        "west" : "r10/f24",
    ]));
    
}
