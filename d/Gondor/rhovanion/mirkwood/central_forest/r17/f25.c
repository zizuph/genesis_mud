#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(20);

    set_distance_to_edge(0);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_ELFPATH_DIR + "p24",
        "north"     : MIRKWOOD_ELFPATH_DIR + "p25",

        "southeast" : "r16/f26",
        "southwest" : "r16/f24",
        "south" : "r16/f25",
        "east" : "r17/f26",
        "northeast" : "r18/f26",
        "west" : "r17/f24",
    ]));
    
}
