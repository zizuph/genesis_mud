#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r27/f19",
        "southwest" : "r27/f17",
        "south" : "r27/f18",
        "northwest" : "r25/f17",
        "east" : "r26/f19",
        "north" : "r25/f18",
        "northeast" : "r25/f19",
        "west" : "r26/f17",
    ]));
    
}
