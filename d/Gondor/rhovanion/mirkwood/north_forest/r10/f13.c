#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(89);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f14",
        "southwest" : "r09/f12",
        "south" : "r09/f13",
        "northwest" : "r11/f12",
        "east" : "r10/f14",
        "north" : "r11/f13",
        "northeast" : "r11/f14",
        "west" : "r10/f12",
    ]));
    
}
