#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r12/f13",
        "southwest" : "r12/f11",
        "south" : "r12/f12",
        "northwest" : "r10/f11",
        "east" : "r11/f13",
        "north" : "r10/f12",
        "northeast" : "r10/f13",
        "west" : "r11/f11",
    ]));
    
}
