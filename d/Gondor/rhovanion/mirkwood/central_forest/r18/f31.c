#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest_edge";

void create_mirkwood_central_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p30",
        
        "southeast" : "r17/f32",
        "southwest" : "r17/f30",
        "south" : "r17/f31",
        "east" : "r18/f32",
        "north" : "r19/f31",
        "northeast" : "r19/f32",
        "west" : "r18/f30",
    ]));
    
}
