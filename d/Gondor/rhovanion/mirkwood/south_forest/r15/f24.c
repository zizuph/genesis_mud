#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r16/f25",
        "southwest" : "r16/f23",
        "south" : "r16/f24",
        "northwest" : "r14/f23",
        "east" : "r15/f25",
        "north" : "r14/f24",
        "northeast" : "r14/f25",
        "west" : "r15/f23",
    ]));
    
}
