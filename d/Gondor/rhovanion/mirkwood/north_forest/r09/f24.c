#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r08/f25",
        "southwest" : "r08/f23",
        "south" : "r08/f24",
        "northwest" : "r10/f23",
        "east" : "r09/f25",
        "north" : "r10/f24",
        "northeast" : "r10/f25",
        "west" : "r09/f23",
    ]));
    
}
