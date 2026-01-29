#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r11/f30",
        "southwest" : "r11/f28",
        "south" : "r11/f29",
        "northwest" : "r13/f28",
        "east" : "r12/f30",
        "north" : "r13/f29",
        "northeast" : "r13/f30",
        "west" : "r12/f28",
    ]));
    
}
