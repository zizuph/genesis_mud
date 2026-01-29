#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r11/f09",
        "southwest" : "r11/f07",
        "south" : "r11/f08",
        "northwest" : "r13/f07",
        "east" : "r12/f09",
        "north" : "r13/f08",
        "northeast" : "r13/f09",
        "west" : "r12/f07",
    ]));
    
}
