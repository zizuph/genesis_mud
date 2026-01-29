#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r15/f29",
        "southwest" : "r15/f27",
        "south" : "r15/f28",
        "northwest" : "r17/f27",
        "east" : "r16/f29",
        "north" : "r17/f28",
        "northeast" : "r17/f29",
        "west" : "r16/f27",
    ]));
    
}
