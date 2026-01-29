#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r05/f12",
        "southwest" : "r05/f10",
        "south" : "r05/f11",
        "northwest" : "r07/f10",
        "east" : "r06/f12",
        "north" : "r07/f11",
        "northeast" : "r07/f12",
        "west" : "r06/f10",
    ]));
    
}
