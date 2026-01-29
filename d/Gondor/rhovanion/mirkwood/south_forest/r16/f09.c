#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r17/f10",
        "southwest" : "r17/f08",
        "south" : "r17/f09",
        "northwest" : "r15/f08",
        "east" : "r16/f10",
        "north" : "r15/f09",
        "northeast" : "r15/f10",
        "west" : "r16/f08",
    ]));
    
}
