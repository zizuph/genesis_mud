#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r28/f23",
        "southwest" : "r28/f21",
        "south" : "r28/f22",
        "northwest" : "r26/f21",
        "east" : "r27/f23",
        "north" : "r26/f22",
        "northeast" : "r26/f23",
        "west" : "r27/f21",
    ]));
    
}
