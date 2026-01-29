#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r08/f09",
        "south" : "r08/f08",
        "east" : "r09/f09",
        "north" : "r10/f08",
        "northeast" : "r10/f09",
        "southwest" : VALE_DIR + "valen9w0",
        "west" : VALE_DIR + "valen10w0",
        "northwest" : VALE_DIR + "valen11w0",
    ]));
    
}
