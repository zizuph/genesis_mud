#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r09/f34",
        "southwest" : "r09/f32",
        "south" : "r09/f33",
        "northwest" : "r11/f32",
        "east" : "r10/f34",
        "north" : "r11/f33",
        "northeast" : "r11/f34",
        "west" : "r10/f32",
    ]));
    
}
