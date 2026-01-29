#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r33/f12",
        "southwest" : "r33/f10",
        "south" : "r33/f11",
        "east" : "r32/f12",
        "north" : "r31/f11",
        "northeast" : "r31/f12",
        "west" : "r32/f10",
    ]));
    
}
