#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r06/f13",
        "southwest" : "r06/f11",
        "south" : "r06/f12",
        "northwest" : "r08/f11",
        "east" : "r07/f13",
        "north" : "r08/f12",
        "northeast" : "r08/f13",
        "west" : "r07/f11",
    ]));
    
}
