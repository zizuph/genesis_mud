#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f33",
        "southwest" : "r09/f31",
        "south" : "r09/f32",
        "northwest" : "r11/f31",
        "east" : "r10/f33",
        "north" : "r11/f32",
        "northeast" : "r11/f33",
        "west" : "r10/f31",
    ]));
    
}
