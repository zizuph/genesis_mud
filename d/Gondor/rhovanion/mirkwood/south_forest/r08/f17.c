#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f18",
        "southwest" : "r09/f16",
        "south" : "r09/f17",
        "northwest" : "r07/f16",
        "east" : "r08/f18",
        "north" : "r07/f17",
        "northeast" : "r07/f18",
        "west" : "r08/f16",
    ]));
    
}
