#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(61);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f37",
        "southwest" : "r08/f35",
        "south" : "r08/f36",
        "northwest" : "r06/f35",
        "east" : "r07/f37",
        "north" : "r06/f36",
        "northeast" : "r06/f37",
        "west" : "r07/f35",
    ]));
    
}
