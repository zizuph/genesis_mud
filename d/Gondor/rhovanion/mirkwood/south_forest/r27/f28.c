#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r28/f29",
        "southwest" : "r28/f27",
        "south" : "r28/f28",
        "northwest" : "r26/f27",
        "east" : "r27/f29",
        "north" : "r26/f28",
        "northeast" : "r26/f29",
        "west" : "r27/f27",
    ]));
    
}
