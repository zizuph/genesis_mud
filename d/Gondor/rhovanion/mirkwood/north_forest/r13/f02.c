#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r12/f03",
        "southwest" : "r12/f01",
        "south" : "r12/f02",
        "northwest" : "r14/f01",
        "east" : "r13/f03",
        "north" : "r14/f02",
        "northeast" : "r14/f03",
        "west" : "r13/f01",
    ]));
    
}
