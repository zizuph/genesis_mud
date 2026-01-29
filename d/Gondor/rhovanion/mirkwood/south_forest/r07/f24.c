#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f25",
        "southwest" : "r08/f23",
        "south" : "r08/f24",
        "northwest" : "r06/f23",
        "east" : "r07/f25",
        "north" : "r06/f24",
        "northeast" : "r06/f25",
        "west" : "r07/f23",
    ]));
    
}
