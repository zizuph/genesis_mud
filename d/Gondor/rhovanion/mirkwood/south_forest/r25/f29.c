#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r26/f30",
        "southwest" : "r26/f28",
        "south" : "r26/f29",
        "northwest" : "r24/f28",
        "east" : "r25/f30",
        "north" : "r24/f29",
        "northeast" : "r24/f30",
        "west" : "r25/f28",
    ]));
    
}
