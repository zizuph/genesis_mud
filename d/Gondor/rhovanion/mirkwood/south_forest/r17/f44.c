#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r18/f45",
        "southwest" : "r18/f43",
        "south" : "r18/f44",
        "northwest" : "r16/f43",
        "east" : "r17/f45",
        "north" : "r16/f44",
        "northeast" : "r16/f45",
        "west" : "r17/f43",
    ]));
    
}
