#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r09/f43",
        "southwest" : "r09/f41",
        "south" : "r09/f42",
        "northwest" : "r11/f41",
        "east" : "r10/f43",
        "north" : "r11/f42",
        "west" : "r10/f41",
    ]));
    
}
