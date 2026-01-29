#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p11",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p12",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p13",
        
        "southeast" : "r16/f13",
        "southwest" : "r16/f11",
        "south" : "r16/f12",
        "east" : "r17/f13",
        "west" : "r17/f11",
    ]));
    
}
