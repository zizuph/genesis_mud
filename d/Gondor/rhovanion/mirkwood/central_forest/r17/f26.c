#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p25",
        
        "southeast" : "r16/f27",
        "southwest" : "r16/f25",
        "south" : "r16/f26",
        "east" : "r17/f27",
        "north" : "r18/f26",
        "northeast" : "r18/f27",
        "west" : "r17/f25",
    ]));
    
}
