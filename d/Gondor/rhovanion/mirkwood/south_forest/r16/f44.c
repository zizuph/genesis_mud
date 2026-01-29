#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r17/f45",
        "southwest" : "r17/f43",
        "south" : "r17/f44",
        "northwest" : "r15/f43",
        "east" : "r16/f45",
        "north" : "r15/f44",
        "northeast" : "r15/f45",
        "west" : "r16/f43",
    ]));
    
}
