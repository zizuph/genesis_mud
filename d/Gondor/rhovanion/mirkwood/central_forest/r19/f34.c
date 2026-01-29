#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p33",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p34",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p35",
        
        "southeast" : "r18/f35",
        "southwest" : "r18/f33",
        "south" : "r18/f34",
        "east" : "r19/f35",
        "west" : "r19/f33",
    ]));
    
}
