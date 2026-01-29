#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p29",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p30",
        "east"      : MIRKWOOD_ELFPATH_DIR + "p31",
        "southeast" : MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f31",
        
        "northwest" : "r03/f29",
        "north" : "r03/f30",
        "northeast" : "r03/f31",
        "west" : "r02/f29",
    ]));
    
}
