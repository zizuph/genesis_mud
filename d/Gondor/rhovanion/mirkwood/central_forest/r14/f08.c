#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r13/f09",
        "south" : "r13/f08",
        "northwest" : "r15/f07",
        "east" : "r14/f09",
        "north" : "r15/f08",
        "northeast" : "r15/f09",
        "southwest" : VALE_DIR + "valen14w0",
        "west" : VALE_DIR + "valen15w0",
    ]));
    
}
