#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(51);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r16/f29",
        "southwest" : "r16/f27",
        "south" : "r16/f28",
        "northwest" : "r18/f27",
        "east" : "r17/f29",
        "north" : "r18/f28",
        "northeast" : "r18/f29",
        "west" : "r17/f27",
    ]));
    
}
