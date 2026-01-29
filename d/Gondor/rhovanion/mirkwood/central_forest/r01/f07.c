#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r00/f08",
        "south" : "r00/f07",
        "east" : "r01/f08",
        "north" : "r02/f07",
        "northeast" : "r02/f08",
        "southwest" : VALE_DIR + "valen1w1",
        "west" : VALE_DIR + "valen2w1",
        "northwest" : VALE_DIR + "valen3w1",
    ]));
    
}
