#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r10/f47",
        "southwest" : "r10/f45",
        "south" : "r10/f46",
        "northwest" : "r08/f45",
        "east" : "r09/f47",
        "north" : "r08/f46",
        "northeast" : "r08/f47",
        "west" : "r09/f45",
    ]));
    
}
