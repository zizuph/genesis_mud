#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(47);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f19",
        "southwest" : "r10/f17",
        "south" : "r10/f18",
        "northwest" : "r12/f17",
        "east" : "r11/f19",
        "north" : "r12/f18",
        "northeast" : "r12/f19",
        "west" : "r11/f17",
    ]));
    
}
