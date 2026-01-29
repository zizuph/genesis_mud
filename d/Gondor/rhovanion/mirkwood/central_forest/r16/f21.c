#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p20",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p21",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p22",
        
        "southeast" : "r15/f22",
        "southwest" : "r15/f20",
        "south" : "r15/f21",
        "east" : "r16/f22",
        "west" : "r16/f20",
    ]));
    
}
