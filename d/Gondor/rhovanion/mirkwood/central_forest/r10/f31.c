#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r09/f32",
        "southwest" : "r09/f30",
        "south" : "r09/f31",
        "northwest" : "r11/f30",
        "east" : "r10/f32",
        "north" : "r11/f31",
        "northeast" : "r11/f32",
        "west" : "r10/f30",
    ]));
    
}
