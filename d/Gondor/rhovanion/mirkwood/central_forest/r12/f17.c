#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(57);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f18",
        "southwest" : "r11/f16",
        "south" : "r11/f17",
        "northwest" : "r13/f16",
        "east" : "r12/f18",
        "north" : "r13/f17",
        "northeast" : "r13/f18",
        "west" : "r12/f16",
    ]));
    
}
