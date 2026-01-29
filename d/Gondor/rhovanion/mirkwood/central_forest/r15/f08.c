#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r14/f09",
        "south" : "r14/f08",
        "northwest" : "r16/f07",
        "east" : "r15/f09",
        "north" : "r16/f08",
        "northeast" : "r16/f09",
        "west" : "r15/f07",
        "southwest" : VALE_DIR + "valen15w0",
    ]));
    
}
