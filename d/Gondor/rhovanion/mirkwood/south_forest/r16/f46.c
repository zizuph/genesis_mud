#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r17/f45",
        "northwest" : "r15/f45",
        "north" : "r15/f46",
        "northeast" : "r15/f47",
        "west" : "r16/f45",
    ]));
    
}
