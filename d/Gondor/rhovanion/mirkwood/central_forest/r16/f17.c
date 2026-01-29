#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(29);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "northeast" : MIRKWOOD_ELFPATH_DIR + "p18",

        "southeast" : "r15/f18",
        "southwest" : "r15/f16",
        "south" : "r15/f17",
        "northwest" : "r17/f16",
        "east" : "r16/f18",
        "north" : "r17/f17",
        "west" : "r16/f16",
    ]));
    
}
