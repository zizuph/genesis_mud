#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r27/f21",
        "southwest" : "r27/f19",
        "south" : "r27/f20",
        "northwest" : "r25/f19",
        "east" : "r26/f21",
        "north" : "r25/f20",
        "northeast" : "r25/f21",
        "west" : "r26/f19",
    ]));
    
}
