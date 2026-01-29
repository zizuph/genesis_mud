#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p10",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p11",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p12",
        
        "southeast" : "r16/f12",
        "southwest" : "r16/f10",
        "south" : "r16/f11",
        "east" : "r17/f12",
        "west" : "r17/f10",
    ]));
    
}
