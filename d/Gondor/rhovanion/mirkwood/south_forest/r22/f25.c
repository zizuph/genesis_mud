#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(14);
    add_mirkwood_exits(([
        "southeast" : "r23/f26",
        "southwest" : "r23/f24",
        "south" : "r23/f25",
        "northwest" : "r21/f24",
        "east" : "r22/f26",
        "north" : "r21/f25",
        "northeast" : "r21/f26",
        "west" : "r22/f24",
    ]));
    
}
