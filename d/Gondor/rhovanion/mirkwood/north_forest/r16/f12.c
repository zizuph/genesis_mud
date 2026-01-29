#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f13",
        "southwest" : "r15/f11",
        "south" : "r15/f12",
        "northwest" : "r17/f11",
        "east" : "r16/f13",
        "north" : "r17/f12",
        "northeast" : "r17/f12",
        "west" : "r16/f11",
    ]));
    
}
