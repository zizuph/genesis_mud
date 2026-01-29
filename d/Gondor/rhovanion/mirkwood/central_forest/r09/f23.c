#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(52);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f24",
        "southwest" : "r08/f22",
        "south" : "r08/f23",
        "northwest" : "r10/f22",
        "east" : "r09/f24",
        "north" : "r10/f23",
        "northeast" : "r09/f24",
        "west" : "r09/f22",
    ]));
    
}
