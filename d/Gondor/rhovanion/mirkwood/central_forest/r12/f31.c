#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f32",
        "southwest" : "r11/f30",
        "south" : "r11/f31",
        "northwest" : "r13/f30",
        "east" : "r12/f32",
        "north" : "r13/f31",
        "northeast" : "r13/f32",
        "west" : "r12/f30",
    ]));
    
}
