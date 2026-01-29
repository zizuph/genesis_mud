#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(31);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p20",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p20",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p21",
        
        "southeast" : "r15/f21",
        "southwest" : "r15/f19",
        "south" : "r15/f20",
        "east" : "r16/f21",
        "west" : "r16/f19",
    ]));
    
}
