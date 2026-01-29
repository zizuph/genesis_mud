#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r20/f24",
        "southwest" : "r20/f22",
        "south" : "r20/f23",
        "northwest" : "r19/f22",
        "east" : "r20/f24",
        "north" : "r19/f23",
        "northeast" : "r19/f24",
        "west" : "r20/f22",
    ]));
    
}
