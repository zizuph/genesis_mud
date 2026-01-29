#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(17);
    add_mirkwood_exits(([
        "southeast" : "r22/f30",
        "southwest" : "r22/f28",
        "south" : "r22/f29",
        "northwest" : "r20/f28",
        "east" : "r21/f30",
        "north" : "r20/f29",
        "northeast" : "r20/f30",
        "west" : "r21/f28",
    ]));
    
}
