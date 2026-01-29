#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "southwest" : MIRKWOOD_ELFPATH_DIR + "p16",
        "south"     : MIRKWOOD_ELFPATH_DIR + "p17",
        
        "southeast" : "r00/f18",
        "northwest" : "r02/f16",
        "east" : "r01/f18",
        "north" : "r02/f17",
        "northeast" : "r02/f18",
        "west" : "r01/f16",
    ]));
    
}
