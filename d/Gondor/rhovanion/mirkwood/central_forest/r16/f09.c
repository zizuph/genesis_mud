#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r15/f10",
        "southwest" : "r15/f08",
        "south" : "r15/f09",
        "northwest" : "r17/f08",
        "east" : "r16/f10",
        "north" : "r17/f09",
        "northeast" : "r17/f10",
        "west" : "r16/f08",
    ]));
    
}
