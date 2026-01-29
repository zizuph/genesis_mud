#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r12/f33",
        "southwest" : "r12/f31",
        "south" : "r12/f32",
        "northwest" : "r10/f31",
        "east" : "r11/f33",
        "north" : "r10/f32",
        "northeast" : "r10/f33",
        "west" : "r11/f31",
    ]));
    
}
