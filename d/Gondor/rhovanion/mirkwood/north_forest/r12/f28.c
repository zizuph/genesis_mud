#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f29",
        "southwest" : "r11/f27",
        "south" : "r11/f28",
        "northwest" : "r13/f27",
        "east" : "r12/f29",
        "north" : "r13/f28",
        "northeast" : "r13/f29",
        "west" : "r12/f27",
    ]));
    
}
