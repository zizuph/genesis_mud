#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r16/f39",
        "southwest" : "r16/f37",
        "south" : "r16/f38",
        "northwest" : "r18/f37",
        "east" : "r17/f39",
        "north" : "r18/f38",
        "west" : "r17/f37",
    ]));
    
}
