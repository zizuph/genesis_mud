#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p23",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p24",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p25",
        
        "northwest" : "r02/f24",
        "east" : "r01/f25",
        "north" : "r02/f24",
        "northeast" : "r02/f25",
        "west" : "r01/f23",
    ]));
    
}
