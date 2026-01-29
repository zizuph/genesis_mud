#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(17);
    add_mirkwood_exits(([
        "southeast" : "r23/f29",
        "southwest" : "r23/f27",
        "south" : "r23/f28",
        "northwest" : "r21/f27",
        "east" : "r22/f29",
        "north" : "r21/f28",
        "northeast" : "r21/f29",
        "west" : "r22/f27",
    ]));
    
}
