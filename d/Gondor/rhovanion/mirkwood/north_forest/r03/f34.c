#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p33",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p34",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p35",
        
        "northwest" : "r04/f33",
        "north" : "r04/f34",
        "northeast" : "r04/f34",
        "west" : "r03/f33",
    ]));
    
}
