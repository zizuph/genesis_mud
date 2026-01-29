#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r28/f17",
        "south" : "r28/f16",
        "northwest" : "r26/f15",
        "east" : "r27/f17",
        "north" : "r26/f16",
        "northeast" : "r26/f17",
        "west" : "r27/f15",
    ]));
    
}
