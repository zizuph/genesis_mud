#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(24);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r10/f46",
        "southwest" : "r10/f44",
        "south" : "r10/f45",
        "northwest" : "r08/f44",
        "east" : "r09/f46",
        "north" : "r08/f45",
        "northeast" : "r08/f46",
        "west" : "r09/f44",
    ]));
    
}
