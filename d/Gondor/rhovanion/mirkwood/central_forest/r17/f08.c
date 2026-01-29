#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p07",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p08",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p09",
        
        "southeast" : "r16/f09",
        "southwest" : "r16/f07",
        "south" : "r16/f08",
        "east" : "r17/f09",
        "west" : "r17/f07",
    ]));
    
}
