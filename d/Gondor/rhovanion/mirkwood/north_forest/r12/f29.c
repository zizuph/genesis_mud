#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(4);
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
