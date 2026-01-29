#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r15/f39",
        "southwest" : "r15/f37",
        "south" : "r15/f38",
        "northwest" : "r17/f37",
        "east" : "r16/f39",
        "north" : "r17/f38",
        "northeast" : "r17/f39",
        "west" : "r16/f37",
    ]));
    
}
