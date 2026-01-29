#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(84);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r07/f14",
        "southwest" : "r07/f12",
        "south" : "r07/f13",
        "northwest" : "r09/f12",
        "east" : "r08/f14",
        "north" : "r09/f13",
        "northeast" : "r09/f14",
        "west" : "r08/f12",
    ]));
    
}
