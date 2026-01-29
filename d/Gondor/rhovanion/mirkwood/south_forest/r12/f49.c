#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : "r13/f48",
        "south" : "r13/f49",
        "northwest" : "r11/f48",
        "east" : "r12/f50",
        "north" : "r11/f49",
        "northeast" : "r11/f50",
        "west" : "r12/f48",
    ]));
    
}
