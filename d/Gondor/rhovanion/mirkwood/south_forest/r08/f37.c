#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(50);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f38",
        "southwest" : "r09/f36",
        "south" : "r09/f37",
        "northwest" : "r07/f36",
        "east" : "r08/f38",
        "north" : "r07/f37",
        "northeast" : "r07/f38",
        "west" : "r08/f36",
    ]));
    
}
