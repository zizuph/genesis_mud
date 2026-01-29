#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r02/f09",
        "southwest" : "r02/f07",
        "south" : "r02/f08",
        "east" : "r03/f09",
        "north" : "r04/f08",
        "northeast" : "r04/f09",
        "west" : "r03/f07",
        "northwest" : VALE_DIR + "valen5w0",
    ]));
    
}
