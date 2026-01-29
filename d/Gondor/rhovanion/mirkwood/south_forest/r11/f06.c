#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r12/f07",
        "south" : "r12/f06",
        "east" : "r11/f07",
        "north" : "r10/f06",
        "northeast" : "r10/f07",
    ]));
    
}
