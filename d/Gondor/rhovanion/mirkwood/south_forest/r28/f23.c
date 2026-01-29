#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r29/f24",
        "southwest" : "r29/f22",
        "south" : "r29/f23",
        "northwest" : "r27/f22",
        "east" : "r28/f24",
        "north" : "r27/f23",
        "northeast" : "r27/f24",
        "west" : "r28/f22",
    ]));
    
}
