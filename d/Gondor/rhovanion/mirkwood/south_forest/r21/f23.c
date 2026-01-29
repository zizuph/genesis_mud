#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r22/f24",
        "southwest" : "r22/f22",
        "south" : "r22/f23",
        "northwest" : "r20/f22",
        "east" : "r21/f24",
        "north" : "r20/f23",
        "northeast" : "r20/f24",
        "west" : "r21/f22",
    ]));
    
}
