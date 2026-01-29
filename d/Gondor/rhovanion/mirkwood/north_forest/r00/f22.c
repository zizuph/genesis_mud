#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p21",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p22",
        "east"      : MIRKWOOD_ELFPATH_DIR + "p23",
        "southeast" : MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f23",
        
        "northwest" : "r01/f22",
        "north" : "r01/f22",
        "northeast" : "r01/f23",
        "west" : "r00/f21",
    ]));
    
}
