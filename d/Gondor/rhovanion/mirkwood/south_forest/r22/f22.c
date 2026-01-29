#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r23/f23",
        "southwest" : "r23/f21",
        "south" : "r23/f22",
        "northwest" : "r21/f21",
        "east" : "r22/f23",
        "north" : "r21/f22",
        "northeast" : "r21/f23",
        "west" : "r22/f21",
    ]));
    
}
