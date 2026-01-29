#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r23/f18",
        "southwest" : "r23/f16",
        "south" : "r23/f17",
        "northwest" : "r21/f16",
        "east" : "r22/f18",
        "north" : "r21/f17",
        "northeast" : "r21/f18",
        "west" : "r22/f16",
    ]));
    
}
