#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r10/f13",
        "southwest" : "r10/f11",
        "south" : "r10/f12",
        "northwest" : "r12/f11",
        "east" : "r11/f13",
        "north" : "r12/f12",
        "northeast" : "r12/f13",
        "west" : "r11/f11",
    ]));
    
}
