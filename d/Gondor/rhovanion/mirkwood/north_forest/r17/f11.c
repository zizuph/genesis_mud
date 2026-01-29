#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r16/f12",
        "southwest" : "r16/f10",
        "south" : "r16/f11",
        "northwest" : "r18/f10",
        "east" : "r17/f12",
        "north" : "r18/f11",
        "northeast" : "r18/f11",
        "west" : "r17/f10",
    ]));
    
}
