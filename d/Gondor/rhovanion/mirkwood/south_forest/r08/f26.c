#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f27",
        "southwest" : "r09/f25",
        "south" : "r09/f26",
        "northwest" : "r07/f25",
        "east" : "r08/f27",
        "north" : "r07/f26",
        "northeast" : "r07/f27",
        "west" : "r08/f25",
    ]));
    
}
