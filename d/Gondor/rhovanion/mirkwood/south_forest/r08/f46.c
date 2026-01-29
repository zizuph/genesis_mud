#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r09/f47",
        "southwest" : "r09/f45",
        "south" : "r09/f46",
        "northwest" : "r07/f45",
        "east" : "r08/f47",
        "north" : "r07/f46",
        "northeast" : "r07/f47",
        "west" : "r08/f45",
    ]));
    
}
