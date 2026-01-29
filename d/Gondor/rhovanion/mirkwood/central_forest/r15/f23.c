#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f24",
        "southwest" : "r14/f22",
        "south" : "r14/f23",
        "northwest" : "r16/f22",
        "east" : "r15/f24",
        "north" : "r16/f23",
        "northeast" : "r16/f24",
        "west" : "r15/f22",
    ]));
    
}
