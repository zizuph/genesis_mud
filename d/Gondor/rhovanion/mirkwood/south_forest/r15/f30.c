#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r16/f31",
        "southwest" : "r16/f29",
        "south" : "r16/f30",
        "northwest" : "r14/f29",
        "east" : "r15/f31",
        "north" : "r14/f30",
        "northeast" : "r14/f31",
        "west" : "r15/f29",
    ]));
    
}
