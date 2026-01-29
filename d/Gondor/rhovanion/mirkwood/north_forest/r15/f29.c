#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f30",
        "southwest" : "r14/f28",
        "south" : "r14/f29",
        "northwest" : "r16/f28",
        "east" : "r15/f30",
        "north" : "r16/f29",
        "northeast" : "r16/f30",
        "west" : "r15/f28",
    ]));
    
}
