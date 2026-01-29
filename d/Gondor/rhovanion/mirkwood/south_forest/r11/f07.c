#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r12/f08",
        "southwest" : "r12/f06",
        "south" : "r12/f07",
        "northwest" : "r10/f06",
        "east" : "r11/f08",
        "north" : "r10/f07",
        "northeast" : "r10/p08-r10",
        "west" : "r11/f06",
    ]));
    
}
