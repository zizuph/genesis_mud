#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r16/f45",
        "south" : "r16/f46",
        "northwest" : "r14/f45",
        "east" : "r15/f47",
        "north" : "r14/f46",
        "northeast" : "r14/f47",
        "west" : "r15/f45",
    ]));
    
}
