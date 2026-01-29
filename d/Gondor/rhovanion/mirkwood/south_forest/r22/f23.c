#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r23/f24",
        "southwest" : "r23/f22",
        "south" : "r23/f23",
        "northwest" : "r21/f22",
        "east" : "r22/f24",
        "north" : "r21/f23",
        "northeast" : "r21/f24",
        "west" : "r22/f22",
    ]));
    
}
