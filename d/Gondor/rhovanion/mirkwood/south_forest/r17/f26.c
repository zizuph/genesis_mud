#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(17);
    add_mirkwood_exits(([
        "southeast" : "r18/f27",
        "southwest" : "r18/f25",
        "south" : "r18/f26",
        "northwest" : "r16/f25",
        "east" : "r17/f27",
        "north" : "r16/f26",
        "northeast" : "r16/f27",
        "west" : "r17/f25",
    ]));
    
}
