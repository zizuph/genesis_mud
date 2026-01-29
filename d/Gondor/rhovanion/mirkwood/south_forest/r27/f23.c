#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r28/f24",
        "southwest" : "r28/f22",
        "south" : "r28/f23",
        "northwest" : "r26/f22",
        "east" : "r27/f24",
        "north" : "r26/f23",
        "northeast" : "r26/f24",
        "west" : "r27/f22",
    ]));
    
}
