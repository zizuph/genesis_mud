#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(94);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f28",
        "southwest" : "r07/m27",
        "south" : "r07/m27",
        "northwest" : "r09/f26",
        "east" : "r08/f28",
        "north" : "r09/f27",
        "northeast" : "r09/f28",
        "west" : "r08/f26",
    ]));
    
}
