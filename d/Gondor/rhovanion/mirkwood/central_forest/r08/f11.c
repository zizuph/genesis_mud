#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r07/f12",
        "southwest" : "r07/f10",
        "south" : "r07/f11",
        "northwest" : "r09/f10",
        "east" : "r08/f12",
        "north" : "r09/f11",
        "northeast" : "r09/f12",
        "west" : "r08/f10",
    ]));
    
}
