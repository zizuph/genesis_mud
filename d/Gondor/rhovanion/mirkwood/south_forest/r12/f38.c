#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r13/f39",
        "southwest" : "r13/f37",
        "south" : "r13/f38",
        "northwest" : "r11/f37",
        "east" : "r12/f39",
        "north" : "r11/f38",
        "northeast" : "r11/f39",
        "west" : "r12/f37",
    ]));
    
}
