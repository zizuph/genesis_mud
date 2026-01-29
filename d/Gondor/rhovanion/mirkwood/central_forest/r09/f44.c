#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r08/f45",
        "southwest" : "r08/f43",
        "south" : "r08/f44",
        "northwest" : "r10/f43",
        "east" : "r09/f45",
        "north" : "r10/f44",
        "northeast" : "r10/f45",
        "west" : "r09/f43",
    ]));
    
}
