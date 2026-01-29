#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(33);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r16/f31",
        "southwest" : "r16/f29",
        "south" : "r16/f30",
        "northwest" : "r18/f29",
        "east" : "r17/f31",
        "north" : "r18/f30",
        "northeast" : "r18/f31",
        "west" : "r17/f29",
    ]));
    
}
