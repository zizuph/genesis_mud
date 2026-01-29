#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p21",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p22",
        
        "southeast" : "r15/f23",
        "southwest" : "r15/f21",
        "south" : "r15/f22",
        "east" : "r16/f23",
        "northeast" : "r17/f23",
        "west" : "r16/f21",
    ]));
    
}
