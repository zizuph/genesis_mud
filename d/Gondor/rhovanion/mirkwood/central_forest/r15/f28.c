#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(54);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r14/f29",
        "southwest" : "r14/f27",
        "south" : "r14/f28",
        "northwest" : "r16/f27",
        "east" : "r15/f29",
        "north" : "r16/f28",
        "northeast" : "r16/f29",
        "west" : "r15/f27",
    ]));
    
}
