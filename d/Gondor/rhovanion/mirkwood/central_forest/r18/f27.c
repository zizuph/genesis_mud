#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p26",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p27",
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p28",

        "southeast" : "r17/f28",
        "southwest" : "r17/f26",
        "south" : "r17/f27",
        "east" : "r18/f28",
        "west" : "r18/f26",
    ]));
    
}
