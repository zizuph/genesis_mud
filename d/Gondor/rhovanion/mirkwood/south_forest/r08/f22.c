#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f23",
        "southwest" : "r09/f21",
        "south" : "r09/f22",
        "northwest" : "r07/f21",
        "east" : "r08/f23",
        "north" : "r07/f22",
        "northeast" : "r07/f23",
        "west" : "r08/f21",
    ]));
    
}
