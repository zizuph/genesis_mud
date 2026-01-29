#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r13/f07",
        "south" : "r13/f06",
        "east" : "r12/f07",
        "north" : "r11/f06",
        "northeast" : "r11/f07",
    ]));
    
}
