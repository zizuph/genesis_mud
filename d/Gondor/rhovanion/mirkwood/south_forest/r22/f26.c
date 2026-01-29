#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(15);
    add_mirkwood_exits(([
        "southeast" : "r23/f27",
        "southwest" : "r23/f25",
        "south" : "r23/f26",
        "northwest" : "r21/f25",
        "east" : "r22/f27",
        "north" : "r21/f26",
        "northeast" : "r21/f27",
        "west" : "r22/f25",
    ]));
    
}
