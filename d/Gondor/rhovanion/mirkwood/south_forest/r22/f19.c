#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r23/f20",
        "southwest" : "r23/f18",
        "south" : "r23/f19",
        "northwest" : "r21/f18",
        "east" : "r22/f20",
        "north" : "r21/f19",
        "northeast" : "r21/f20",
        "west" : "r22/f18",
    ]));
    
}
