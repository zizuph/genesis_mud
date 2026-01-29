#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r13/f03",
        "southwest" : "r13/f01",
        "south" : "r13/f02",
        "east" : "r14/f03",
        "north" : "r15/f02",
        "northeast" : "r15/f03",
        "west" : "r14/f01",
    ]));
    
}
