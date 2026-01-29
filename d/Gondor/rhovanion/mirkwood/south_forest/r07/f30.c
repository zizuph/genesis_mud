#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f31",
        "southwest" : "r08/f29",
        "south" : "r08/f30",
        "northwest" : "r06/f29",
        "east" : "r07/f31",
        "north" : "r06/f30",
        "northeast" : "r06/f31",
        "west" : "r07/f29",
    ]));
    
}
