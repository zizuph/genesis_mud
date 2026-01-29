#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r23/f13",
        "southwest" : "r23/f11",
        "south" : "r23/f12",
        "northwest" : "r21/f11",
        "east" : "r22/f13",
        "north" : "r21/f12",
        "northeast" : "r21/f13",
        "west" : "r22/f11",
    ]));
    
}
