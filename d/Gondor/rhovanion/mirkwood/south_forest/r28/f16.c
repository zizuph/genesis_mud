#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r29/f17",
        "southwest" : "r29/f15",
        "south" : "r29/f16",
        "northwest" : "r27/f15",
        "east" : "r28/f17",
        "north" : "r27/f16",
        "northeast" : "r27/f17",
    ]));
    
}
