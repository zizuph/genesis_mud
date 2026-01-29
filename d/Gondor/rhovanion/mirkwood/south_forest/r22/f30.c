#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r23/f31",
        "southwest" : "r23/f29",
        "south" : "r23/f30",
        "northwest" : "r21/f29",
        "east" : "r22/f31",
        "north" : "r21/f30",
        "northeast" : "r21/f31",
        "west" : "r22/f29",
    ]));
    
}
