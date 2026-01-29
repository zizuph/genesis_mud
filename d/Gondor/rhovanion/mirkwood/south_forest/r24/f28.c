#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r25/f29",
        "southwest" : "r25/f27",
        "south" : "r25/f28",
        "northwest" : "r23/f27",
        "east" : "r24/f29",
        "north" : "r23/f28",
        "northeast" : "r23/f29",
        "west" : "r24/f27",
    ]));
    
}
