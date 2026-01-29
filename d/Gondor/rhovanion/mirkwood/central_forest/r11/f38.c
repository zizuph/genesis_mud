#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r10/f39",
        "southwest" : "r10/f37",
        "south" : "r10/f38",
        "northwest" : "r12/f37",
        "east" : "r11/f39",
        "north" : "r12/f38",
        "northeast" : "r12/f39",
        "west" : "r11/f37",
    ]));
    
}
