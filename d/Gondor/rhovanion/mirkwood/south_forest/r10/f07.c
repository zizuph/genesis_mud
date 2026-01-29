#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r11/f08",
        "southwest" : "r11/f06",
        "south" : "r11/f07",
        "northwest" : "r09/f06",
        "east" : "r10/p08-r10",
        "north" : "r09/f07",
        "northeast" : "r09/p08-r09",
        "west" : "r10/f06",
    ]));
    
}
