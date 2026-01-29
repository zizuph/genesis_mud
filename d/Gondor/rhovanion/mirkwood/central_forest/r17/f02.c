#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p01",
        "north" : MIRKWOOD_ELFPATH_DIR + "p02",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p03",

        "southwest" : VALE_DIR + "valen17w6",
        "south" : VALE_DIR + "valen17w5",
        "west" : VALE_DIR + "valen18w6",
        
        "southeast" : "r16/f03",
        "east" : "r17/f03",
    ]));
    
}
