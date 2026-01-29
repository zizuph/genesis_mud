#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r15/f09",
        "southwest" : "r15/f07",
        "south" : "r15/f08",
        "northwest" : "r17/f07",
        "east" : "r16/f09",
        "north" : "r17/f08",
        "northeast" : "r17/f09",
        "west" : "r16/f07",
    ]));
    
}
