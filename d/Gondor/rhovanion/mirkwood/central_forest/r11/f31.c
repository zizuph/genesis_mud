#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f32",
        "southwest" : "r10/f30",
        "south" : "r10/f31",
        "northwest" : "r12/f30",
        "east" : "r11/f32",
        "north" : "r12/f31",
        "northeast" : "r12/f32",
        "west" : "r11/f30",
    ]));
    
}
