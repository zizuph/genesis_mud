#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(46);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f17",
        "southwest" : "r11/f15",
        "south" : "r11/f16",
        "northwest" : "r13/f15",
        "east" : "r12/f17",
        "north" : "r13/f16",
        "northeast" : "r13/f16",
        "west" : "r12/f15",
    ]));
    
}
