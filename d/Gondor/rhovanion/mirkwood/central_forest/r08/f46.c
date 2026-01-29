#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r07/f47",
        "southwest" : "r07/f45",
        "south" : "r07/f46",
        "northwest" : "r09/f45",
        "east" : "r08/f47",
        "north" : "r09/f46",
        "northeast" : "r09/f47",
        "west" : "r08/f45",
    ]));
    
}
