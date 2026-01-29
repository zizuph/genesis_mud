#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(71);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r07/f13",
        "southwest" : "r07/f11",
        "south" : "r07/f12",
        "northwest" : "r09/f11",
        "east" : "r08/f13",
        "north" : "r09/f12",
        "northeast" : "r09/f13",
        "west" : "r08/f11",
    ]));
    
}
