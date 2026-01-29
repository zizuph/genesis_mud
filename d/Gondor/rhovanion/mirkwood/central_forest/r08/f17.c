#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(41);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r07/f18",
        "southwest" : "r07/f16",
        "south" : "r07/f17",
        "northwest" : "r09/f16",
        "east" : "r08/f18",
        "north" : "r09/f17",
        "northeast" : "r09/f18",
        "west" : "r08/f16",
    ]));
    
}
