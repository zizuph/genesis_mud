#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r16/f26",
        "southwest" : "r16/f24",
        "south" : "r16/f25",
        "northwest" : "r18/f24",
        "east" : "r17/f26",
        "north" : "r18/f25",
        "northeast" : "r18/f26",
        "west" : "r17/f24",
    ]));
    
}
