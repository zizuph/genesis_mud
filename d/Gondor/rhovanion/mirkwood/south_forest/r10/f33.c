#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f34",
        "southwest" : "r11/f32",
        "south" : "r11/f33",
        "northwest" : "r09/f32",
        "east" : "r10/f34",
        "north" : "r09/f33",
        "northeast" : "r09/f34",
        "west" : "r10/f32",
    ]));
    
}
