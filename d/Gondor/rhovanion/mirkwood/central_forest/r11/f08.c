#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r10/f09",
        "south" : "r10/f08",
        "east" : "r11/f09",
        "north" : "r12/f08",
        "northeast" : "r12/f09",
        "southwest" : VALE_DIR + "valen11w0",
        "west" : VALE_DIR + "valen12w0",
        "northwest" : VALE_DIR + "valen13w0",
    ]));
    
}
