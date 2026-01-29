#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r24/f26",
        "southwest" : "r24/f24",
        "south" : "r24/f25",
        "northwest" : "r22/f24",
        "east" : "r23/f26",
        "north" : "r22/f25",
        "northeast" : "r22/f26",
        "west" : "r23/f24",
    ]));
    
}
