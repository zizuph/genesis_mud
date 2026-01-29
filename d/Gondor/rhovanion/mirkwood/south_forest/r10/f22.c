#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f23",
        "southwest" : "r11/f21",
        "south" : "r11/f22",
        "northwest" : "r09/f21",
        "east" : "r10/f23",
        "north" : "r09/f22",
        "northeast" : "r09/f23",
        "west" : "r10/f21",
    ]));
    
}
