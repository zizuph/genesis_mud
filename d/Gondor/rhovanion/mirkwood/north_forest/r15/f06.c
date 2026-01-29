#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r14/f07",
        "southwest" : "r14/f05",
        "south" : "r14/f06",
        "northwest" : "r16/f05",
        "east" : "r15/f07",
        "north" : "r16/f06",
        "northeast" : "r16/f07",
        "west" : "r15/f05",
    ]));
    
}
