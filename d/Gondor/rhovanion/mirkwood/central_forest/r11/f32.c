#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f33",
        "southwest" : "r10/f31",
        "south" : "r10/f32",
        "northwest" : "r12/f31",
        "east" : "r11/f33",
        "north" : "r12/f32",
        "northeast" : "r12/f33",
        "west" : "r11/f31",
    ]));
    
}
