#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p09",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p10",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p11",
        
        "southeast" : "r16/f11",
        "southwest" : "r16/f09",
        "south" : "r16/f10",
        "east" : "r17/f11",
        "west" : "r17/f09",
    ]));
    
}
