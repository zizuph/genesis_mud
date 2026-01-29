#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r11/f15",
        "southwest" : "r11/f13",
        "south" : "r11/f14",
        "northwest" : "r09/f13",
        "east" : "r10/f15",
        "north" : "r09/f14",
        "northeast" : "r09/f15",
        "west" : "r10/f13",
    ]));
    
}
