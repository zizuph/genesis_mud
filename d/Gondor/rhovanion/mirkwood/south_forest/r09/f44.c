#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r10/f45",
        "southwest" : "r10/f43",
        "south" : "r10/f44",
        "northwest" : "r08/f43",
        "east" : "r09/f45",
        "north" : "r08/f44",
        "northeast" : "r08/f45",
        "west" : "r09/f43",
    ]));
    
}
