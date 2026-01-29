#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r09/f12",
        "southwest" : "r09/f10",
        "south" : "r09/f11",
        "northwest" : "r07/f10",
        "east" : "r08/f12",
        "north" : "r07/f11",
        "northeast" : "r07/f12",
        "west" : "r08/f10",
    ]));
    
}
