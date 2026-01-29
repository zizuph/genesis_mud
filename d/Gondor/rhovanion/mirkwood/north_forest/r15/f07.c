#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f08",
        "southwest" : "r14/f06",
        "south" : "r14/f07",
        "northwest" : "r16/f06",
        "east" : "r15/f08",
        "north" : "r16/f07",
        "northeast" : "r16/f08",
        "west" : "r15/f06",
    ]));
    
}
