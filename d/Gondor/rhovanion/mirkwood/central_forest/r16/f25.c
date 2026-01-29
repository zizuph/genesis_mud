#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(40);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r15/f26",
        "southwest" : "r15/f24",
        "south" : "r15/f25",
        "northwest" : "r17/f24",
        "east" : "r16/f26",
        "north" : "r17/f25",
        "northeast" : "r17/f26",
        "west" : "r16/f24",
    ]));
    
}
