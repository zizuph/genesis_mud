#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f34",
        "southwest" : "r10/f32",
        "south" : "r10/f33",
        "northwest" : "r12/f32",
        "east" : "r11/f34",
        "north" : "r12/f33",
        "northeast" : "r12/f34",
        "west" : "r11/f32",
    ]));
    
}
