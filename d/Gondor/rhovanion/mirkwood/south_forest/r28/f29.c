#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r29/f30",
        "southwest" : "r29/f28",
        "south" : "r29/f29",
        "northwest" : "r27/f28",
        "east" : "r28/f30",
        "north" : "r27/f29",
        "northeast" : "r27/f30",
        "west" : "r28/f28",
    ]));
    
}
