#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r11/f31",
        "southwest" : "r11/f29",
        "south" : "r11/f30",
        "northwest" : "r13/f29",
        "east" : "r12/f31",
        "north" : "r13/f30",
        "northeast" : "r13/f31",
        "west" : "r12/f29",
    ]));
    
}
