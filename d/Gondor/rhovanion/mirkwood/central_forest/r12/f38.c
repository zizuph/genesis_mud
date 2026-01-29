#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r11/f39",
        "southwest" : "r11/f37",
        "south" : "r11/f38",
        "northwest" : "r13/f37",
        "east" : "r12/f39",
        "north" : "r13/f38",
        "northeast" : "r13/f39",
        "west" : "r12/f37",
    ]));
    
}
