#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(73);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r06/m31",
        "southwest" : "r06/m29",
        "south" : "r06/m30",
        "northwest" : "r08/f29",
        "east" : "r07/f31",
        "north" : "r08/f30",
        "northeast" : "r08/f31",
        "west" : "r07/f29",
    ]));
    
}
