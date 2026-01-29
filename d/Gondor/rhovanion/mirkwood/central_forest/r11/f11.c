#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r10/f12",
        "southwest" : "r10/f10",
        "south" : "r10/f11",
        "northwest" : "r12/f10",
        "east" : "r11/f12",
        "north" : "r12/f11",
        "northeast" : "r12/f12",
        "west" : "r11/f10",
    ]));
    
}
