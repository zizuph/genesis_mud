#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r14/f09",
        "southwest" : "r14/f07",
        "south" : "r14/f08",
        "northwest" : "r16/f07",
        "east" : "r15/f09",
        "north" : "r16/f08",
        "northeast" : "r16/f09",
        "west" : "r15/f07",
    ]));
    
}
