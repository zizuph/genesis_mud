#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r24/f30",
        "southwest" : "r24/f28",
        "south" : "r24/f29",
        "northwest" : "r22/f28",
        "east" : "r23/f30",
        "north" : "r22/f29",
        "northeast" : "r22/f30",
        "west" : "r23/f28",
    ]));
    
}
