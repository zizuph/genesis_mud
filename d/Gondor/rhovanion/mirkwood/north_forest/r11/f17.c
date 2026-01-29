#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r10/f18",
        "southwest" : "r10/f16",
        "south" : "r10/f17",
        "northwest" : "r12/f16",
        "east" : "r11/f18",
        "north" : "r12/f17",
        "northeast" : "r12/f17",
        "west" : "r11/f16",
    ]));
    
}
