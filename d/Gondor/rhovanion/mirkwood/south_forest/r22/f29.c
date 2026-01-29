#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(16);
    add_mirkwood_exits(([
        "southeast" : "r23/f30",
        "southwest" : "r23/f28",
        "south" : "r23/f29",
        "northwest" : "r21/f28",
        "east" : "r22/f30",
        "north" : "r21/f29",
        "northeast" : "r21/f30",
        "west" : "r22/f28",
    ]));
    
}
