#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r29/f25",
        "southwest" : "r29/f23",
        "south" : "r29/f24",
        "northwest" : "r27/f23",
        "east" : "r28/f25",
        "north" : "r27/f24",
        "northeast" : "r27/f25",
        "west" : "r28/f23",
    ]));
    
}
