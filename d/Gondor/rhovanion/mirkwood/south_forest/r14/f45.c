#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r15/f46",
        "southwest" : "r15/f44",
        "south" : "r15/f45",
        "northwest" : "r13/f44",
        "east" : "r14/f46",
        "north" : "r13/f45",
        "northeast" : "r13/f46",
        "west" : "r14/f44",
    ]));
    
}
