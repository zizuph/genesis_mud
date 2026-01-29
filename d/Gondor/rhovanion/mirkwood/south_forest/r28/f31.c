#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r29/f32",
        "southwest" : "r29/f30",
        "south" : "r29/f31",
        "northwest" : "r27/f30",
        "west" : "r28/f30",
    ]));
    
}
