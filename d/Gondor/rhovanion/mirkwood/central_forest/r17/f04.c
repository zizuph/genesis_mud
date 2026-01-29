#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p03",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p04",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p05",
        
        "southeast" : "r16/f05",
        "southwest" : "r16/f03",
        "south" : "r16/f04",
        "east" : "r17/f05",
        "west" : "r17/f03",
    ]));
    
}
