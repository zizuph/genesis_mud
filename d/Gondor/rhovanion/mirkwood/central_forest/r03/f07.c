#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r02/f08",
        "south" : "r02/f07",
        "east" : "r03/f08",
        "northeast" : "r04/f08",
        "north" : VALE_DIR + "valen5w0",
        "northwest" : VALE_DIR + "valen5w1",
        "west" : VALE_DIR + "valen4w1",
        "southwest" : VALE_DIR + "valen3w1",
    ]));
    
}
