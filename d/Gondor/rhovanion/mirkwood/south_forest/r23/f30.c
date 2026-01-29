#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r24/f31",
        "southwest" : "r24/f29",
        "south" : "r24/f30",
        "northwest" : "r22/f29",
        "east" : "r23/f31",
        "north" : "r22/f30",
        "northeast" : "r22/f31",
        "west" : "r23/f29",
    ]));
    
}
