#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(17);
    add_mirkwood_exits(([
        "southeast" : "r18/f26",
        "southwest" : "r18/f24",
        "south" : "r18/f25",
        "northwest" : "r16/f24",
        "east" : "r17/f26",
        "north" : "r16/f25",
        "northeast" : "r16/f26",
        "west" : "r17/f24",
    ]));
    
}
