#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(31);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f25",
        "southwest" : "r11/f23",
        "south" : "r11/f24",
        "northwest" : "r13/f23",
        "east" : "r12/f25",
        "north" : "r13/f24",
        "northeast" : "r13/f25",
        "west" : "r12/f23",
    ]));
    
}
