#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r20/f11",
        "south" : "r20/f10",
        "northwest" : "r18/f09",
        "east" : "r19/f11",
        "north" : "r18/f10",
        "northeast" : "r18/f11",
        "west" : "r19/f09",
    ]));
    
}
