#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(4);
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
