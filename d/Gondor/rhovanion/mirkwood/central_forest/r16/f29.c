#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(74);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r15/f30",
        "southwest" : "r15/f28",
        "south" : "r15/f29",
        "northwest" : "r17/f28",
        "east" : "r16/f30",
        "north" : "r17/f29",
        "northeast" : "r17/f30",
        "west" : "r16/f28",
    ]));
    
}
