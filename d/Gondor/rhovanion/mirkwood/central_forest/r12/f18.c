#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(78);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r11/f19",
        "southwest" : "r11/f17",
        "south" : "r11/f18",
        "northwest" : "r13/f17",
        "east" : "r12/f19",
        "north" : "r13/f18",
        "northeast" : "r13/f19",
        "west" : "r12/f17",
    ]));
    
}
