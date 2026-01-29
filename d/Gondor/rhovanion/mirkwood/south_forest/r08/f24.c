#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f25",
        "southwest" : "r09/f23",
        "south" : "r09/f24",
        "northwest" : "r07/f23",
        "east" : "r08/f25",
        "north" : "r07/f24",
        "northeast" : "r07/f25",
        "west" : "r08/f23",
    ]));
    
}
