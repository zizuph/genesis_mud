#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r09/f35",
        "southwest" : "r09/f33",
        "south" : "r09/f34",
        "northwest" : "r11/f33",
        "east" : "r10/f35",
        "north" : "r11/f34",
        "west" : "r10/f33",
    ]));
    
}
