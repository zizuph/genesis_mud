#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p24",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p25",
        "east"      : MIRKWOOD_ELFPATH_DIR + "p26",
        "southeast" : MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f26",
        
        "northwest" : "r02/f24",
        "north" : "r02/f25",
        "northeast" : "r02/f26",
        "west" : "r01/f24",
    ]));
    
}
