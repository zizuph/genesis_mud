#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(31);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r11/f20",
        "southwest" : "r12/f18",
        "south" : "r11/f19",
        "northwest" : "r13/f18",
        "east" : "r12/f20",
        "north" : "r13/f19",
        "northeast" : "r13/f20",
        "west" : "r12/f18",
    ]));
    
}
