#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r16/f37",
        "southwest" : "r16/f35",
        "south" : "r16/f36",
        "northwest" : "r18/f35",
        "east" : "r17/f37",
        "north" : "r18/f36",
        "northeast" : "r18/f37",
        "west" : "r17/f35",
    ]));
    
}
