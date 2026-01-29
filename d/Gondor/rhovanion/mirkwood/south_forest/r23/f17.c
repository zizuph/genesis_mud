#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r24/f18",
        "southwest" : "r24/f16",
        "south" : "r24/f17",
        "northwest" : "r22/f16",
        "east" : "r23/f18",
        "north" : "r22/f17",
        "northeast" : "r22/f18",
        "west" : "r23/f16",
    ]));
    
}
