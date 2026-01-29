#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r25/f30",
        "southwest" : "r25/f28",
        "south" : "r25/f29",
        "northwest" : "r23/f28",
        "east" : "r24/f30",
        "north" : "r23/f29",
        "northeast" : "r23/f30",
        "west" : "r24/f28",
    ]));
    
}
