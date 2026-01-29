#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p27",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p28",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p29",
        
        "southeast" : "r17/f29",
        "southwest" : "r17/f27",
        "south" : "r17/f28",
        "east" : "r18/f29",
        "west" : "r18/f27",
    ]));
    
}
