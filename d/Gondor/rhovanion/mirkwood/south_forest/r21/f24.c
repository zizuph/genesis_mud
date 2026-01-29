#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(14);
    add_mirkwood_exits(([
        "southeast" : "r22/f25",
        "southwest" : "r22/f23",
        "south" : "r22/f24",
        "northwest" : "r20/f23",
        "east" : "r21/f25",
        "north" : "r20/f24",
        "northeast" : "r20/f25",
        "west" : "r21/f23",
    ]));
    
}
