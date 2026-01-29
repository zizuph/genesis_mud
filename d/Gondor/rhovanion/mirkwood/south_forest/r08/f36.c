#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(44);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f37",
        "southwest" : "r09/f35",
        "south" : "r09/f36",
        "northwest" : "r07/f35",
        "east" : "r08/f37",
        "north" : "r07/f36",
        "northeast" : "r07/f37",
        "west" : "r08/f35",
    ]));
    
}
