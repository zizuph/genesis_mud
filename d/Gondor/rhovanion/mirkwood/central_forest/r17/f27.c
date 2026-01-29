#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(44);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r16/f28",
        "southwest" : "r16/f26",
        "south" : "r16/f27",
        "northwest" : "r18/f26",
        "east" : "r17/f28",
        "north" : "r18/f27",
        "northeast" : "r18/f28",
        "west" : "r17/f26",
    ]));
    
}
