#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p05",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p06",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p07",
        
        "northwest" : "r02/f05",
        "east" : "r01/f07",
        "north" : "r02/f06",
        "northeast" : "r02/f07",
        "west" : "r01/f05",
    ]));
    
}
