#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f27",
        "southwest" : "r08/f25",
        "south" : "r08/f26",
        "northwest" : "r10/f25",
        "east" : "r09/f27",
        "north" : "r10/f26",
        "northeast" : "r10/f27",
        "west" : "r09/f25",
    ]));
    
}
