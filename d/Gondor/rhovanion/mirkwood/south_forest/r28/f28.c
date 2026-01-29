#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r29/f29",
        "southwest" : "r29/f27",
        "south" : "r29/f28",
        "northwest" : "r27/f27",
        "east" : "r28/f29",
        "north" : "r27/f28",
        "northeast" : "r27/f29",
        "west" : "r28/f27",
    ]));
    
}
