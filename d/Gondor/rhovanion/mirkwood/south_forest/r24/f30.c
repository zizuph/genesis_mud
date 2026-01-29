#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r25/f31",
        "southwest" : "r25/f29",
        "south" : "r25/f30",
        "northwest" : "r23/f29",
        "east" : "r24/f31",
        "north" : "r23/f30",
        "northeast" : "r23/f31",
        "west" : "r24/f29",
    ]));
    
}
