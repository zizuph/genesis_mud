#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p02",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p03",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p04",

        "southwest" : VALE_DIR + "valen17w5",
        
        "southeast" : "r16/f04",
        "south" : "r16/f03",
        "east" : "r17/f04",
        "west" : "r17/f02",
    ]));
    
}
