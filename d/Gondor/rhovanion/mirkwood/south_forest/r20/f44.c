#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r20/f45",
        "southwest" : "r20/f43",
        "south" : "r20/f44",
        "northwest" : "r19/f43",
        "east" : "r20/f45",
        "north" : "r19/f44",
        "northeast" : "r19/f45",
        "west" : "r20/f43",
    ]));
    
}
