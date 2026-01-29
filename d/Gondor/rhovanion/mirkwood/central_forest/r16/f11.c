#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r15/f12",
        "southwest" : "r15/f10",
        "south" : "r15/f11",
        "northwest" : "r17/f10",
        "east" : "r16/f12",
        "north" : "r17/f11",
        "northeast" : "r17/f12",
        "west" : "r16/f10",
    ]));
    
}
