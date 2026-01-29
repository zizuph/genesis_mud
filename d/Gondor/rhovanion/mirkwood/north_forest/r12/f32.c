#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r11/f33",
        "southwest" : "r11/f31",
        "south" : "r11/f32",
        "northwest" : "r13/f31",
        "east" : "r12/f33",
        "north" : "r13/f32",
        "northeast" : "r13/f33",
        "west" : "r12/f31",
    ]));
    
}
