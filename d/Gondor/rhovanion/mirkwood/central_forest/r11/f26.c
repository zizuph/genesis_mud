#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r10/f27",
        "southwest" : "r10/f25",
        "south" : "r10/f26",
        "northwest" : "r12/f25",
        "east" : "r11/f27",
        "north" : "r12/f26",
        "northeast" : "r12/f27",
        "west" : "r11/f25",
    ]));
    
}
