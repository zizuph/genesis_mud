#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r12/f12",
        "southwest" : "r12/f10",
        "south" : "r12/f11",
        "northwest" : "r10/f10",
        "east" : "r11/f12",
        "north" : "r10/f11",
        "northeast" : "r10/f12",
        "west" : "r11/f10",
    ]));
    
}
