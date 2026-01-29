#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r14/f08",
        "northwest" : "r16/f06",
        "east" : "r15/f08",
        "north" : "r16/f07",
        "northeast" : "r16/f08",
        "west" : "r15/f06",
        "south" : VALE_DIR + "valen15w0",
        "southwest" : VALE_DIR + "valen15w1",
    ]));
    
}
