#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p32",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p33",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p34",
        
        "northwest" : "r04/f32",
        "east" : "r03/f34",
        "north" : "r04/f33",
        "northeast" : "r04/f34",
        "west" : "r03/f32",
    ]));
    
}
