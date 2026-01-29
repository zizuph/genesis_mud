#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r24/f25",
        "southwest" : "r24/f23",
        "south" : "r24/f24",
        "northwest" : "r22/f23",
        "east" : "r23/f25",
        "north" : "r22/f24",
        "northeast" : "r22/f25",
        "west" : "r23/f23",
    ]));
    
}
