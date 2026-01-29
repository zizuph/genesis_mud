#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(26);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f26",
        "southwest" : "r08/f24",
        "south" : "r08/f25",
        "northwest" : "r10/f24",
        "east" : "r09/f26",
        "north" : "r10/f25",
        "northeast" : "r10/f26",
        "west" : "r09/f24",
    ]));
    
}
