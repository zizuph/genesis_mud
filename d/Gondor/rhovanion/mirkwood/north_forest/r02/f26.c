#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "south"     : MIRKWOOD_ELFPATH_DIR + "p26",
        "southeast" : MIRKWOOD_ELFPATH_DIR + "p27",
        
        "southwest" : "r01/f25",
        "northwest" : "r03/f26",
        "east" : "r02/f27",
        "north" : "r03/f26",
        "northeast" : "r03/f27",
        "west" : "r02/f25",
    ]));
    
}
