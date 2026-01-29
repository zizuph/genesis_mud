#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r10/f31",
        "southwest" : "r10/f29",
        "south" : "r10/f30",
        "northwest" : "r12/f29",
        "east" : "r11/f31",
        "north" : "r12/f30",
        "northeast" : "r12/f31",
        "west" : "r11/f29",
    ]));
    
}
