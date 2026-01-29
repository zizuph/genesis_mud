#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r09/f36",
        "southwest" : "r09/f34",
        "south" : "r09/f35",
        "northwest" : "r11/f34",
        "west" : "r10/f34",
    ]));
    
}
