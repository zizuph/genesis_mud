#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : "r12/f49",
        "south" : "r12/f50",
        "northwest" : "r10/f49",
        "north" : "r10/f50",
        "west" : "r11/f49",
    ]));
    
}
