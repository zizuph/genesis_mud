#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r15/f37",
        "southwest" : "r15/f35",
        "south" : "r15/f36",
        "northwest" : "r17/f35",
        "east" : "r16/f37",
        "north" : "r17/f36",
        "northeast" : "r17/f37",
        "west" : "r16/f35",
    ]));
    
}
