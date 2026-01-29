#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f24",
        "southwest" : "r15/f22",
        "south" : "r15/f23",
        "northwest" : "r17/f22",
        "east" : "r16/f24",
        "north" : "r17/f23",
        "northeast" : "r17/f24",
        "west" : "r16/f22",
    ]));
    
}
