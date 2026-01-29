#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(58);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f23",
        "southwest" : "r07/f21",
        "south" : "r07/f22",
        "northwest" : "r09/f21",
        "east" : "r08/f23",
        "north" : "r09/f22",
        "northeast" : "r09/f23",
        "west" : "r08/f21",
    ]));
    
}
