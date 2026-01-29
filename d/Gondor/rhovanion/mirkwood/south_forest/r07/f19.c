#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f20",
        "southwest" : "r08/f18",
        "south" : "r08/f19",
        "northwest" : "r06/f18",
        "east" : "r07/f20",
        "north" : "r06/f19",
        "northeast" : "r06/f20",
        "west" : "r07/f18",
    ]));
    
}
