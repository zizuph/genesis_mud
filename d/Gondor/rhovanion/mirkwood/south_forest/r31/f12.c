#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r32/f13",
        "southwest" : "r32/f11",
        "south" : "r32/f12",
        "east" : "r31/f13",
        "north" : "r30/f12",
        "northeast" : "r30/f13",
        "west" : "r31/f11",
    ]));
    
}
