#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f32",
        "southwest" : "r12/f30",
        "south" : "r12/f31",
        "northwest" : "r10/f30",
        "east" : "r11/f32",
        "north" : "r10/f31",
        "northeast" : "r10/f32",
        "west" : "r11/f30",
    ]));
    
}
