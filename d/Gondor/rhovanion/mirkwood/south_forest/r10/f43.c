#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f44",
        "southwest" : "r11/f42",
        "south" : "r11/f43",
        "northwest" : "r09/f42",
        "east" : "r10/f44",
        "north" : "r09/f43",
        "northeast" : "r09/f44",
        "west" : "r10/f42",
    ]));
    
}
