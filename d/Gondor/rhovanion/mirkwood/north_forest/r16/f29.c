#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
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
