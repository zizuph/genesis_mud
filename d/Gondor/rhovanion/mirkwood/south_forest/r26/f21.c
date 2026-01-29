#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(9);
    add_mirkwood_exits(([
        "southeast" : "r27/f22",
        "southwest" : "r27/f20",
        "south" : "r27/f21",
        "northwest" : "r25/f20",
        "east" : "r26/f22",
        "north" : "r25/f21",
        "northeast" : "r25/f22",
        "west" : "r26/f20",
    ]));
    
}
