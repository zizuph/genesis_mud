#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(62);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f25",
        "southwest" : "r07/f23",
        "south" : "r07/f24",
        "northwest" : "r09/f23",
        "east" : "r08/f25",
        "north" : "r09/f24",
        "northeast" : "r08/f25",
        "west" : "r08/f23",
    ]));
    
}
