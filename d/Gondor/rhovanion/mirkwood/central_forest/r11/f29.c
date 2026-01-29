#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r10/f30",
        "southwest" : "r10/f28",
        "south" : "r10/f29",
        "northwest" : "r12/f28",
        "east" : "r11/f30",
        "north" : "r12/f29",
        "northeast" : "r12/f30",
        "west" : "r11/f28",
    ]));
    
}
