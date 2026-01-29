#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r20/f46",
        "southwest" : "r20/f44",
        "south" : "r20/f45",
        "northwest" : "r19/f44",
        "east" : "r20/f46",
        "north" : "r19/f45",
        "northeast" : "r19/f46",
        "west" : "r20/f44",
    ]));
    
}
