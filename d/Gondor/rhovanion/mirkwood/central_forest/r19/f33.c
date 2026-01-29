#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p32",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p33",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p34",
        
        "southeast" : "r18/f34",
        "southwest" : "r18/f32",
        "south" : "r18/f33",
        "east" : "r19/f34",
        "west" : "r19/f32",
    ]));
    
}
