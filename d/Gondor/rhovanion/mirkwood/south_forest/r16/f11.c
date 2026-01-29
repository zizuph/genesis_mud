#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r17/f12",
        "southwest" : "r17/f10",
        "south" : "r17/f11",
        "northwest" : "r15/f10",
        "east" : "r16/f12",
        "north" : "r15/f11",
        "northeast" : "r15/f12",
        "west" : "r16/f10",
    ]));
    
}
