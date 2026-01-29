#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r15/f27",
        "southwest" : "r15/f25",
        "south" : "r15/f26",
        "northwest" : "r17/f25",
        "east" : "r16/f27",
        "north" : "r17/f26",
        "northeast" : "r17/f27",
        "west" : "r16/f25",
    ]));
    
}
