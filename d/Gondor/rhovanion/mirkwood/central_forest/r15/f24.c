#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f25",
        "southwest" : "r14/f23",
        "south" : "r14/f24",
        "northwest" : "r16/f23",
        "east" : "r15/f25",
        "north" : "r16/f24",
        "northeast" : "r16/f25",
        "west" : "r15/f23",
    ]));
    
}
