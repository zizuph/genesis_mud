#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r18/f10",
        "south" : "r18/f09",
        "northwest" : "r16/f08",
        "east" : "r17/f10",
        "north" : "r16/f09",
        "northeast" : "r16/f10",
        "west" : "r17/f08",
    ]));
    
}
