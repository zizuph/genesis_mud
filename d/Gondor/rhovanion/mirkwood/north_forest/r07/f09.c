#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(36);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f10",
        "southwest" : "r06/f08",
        "south" : "r06/f09",
        "northwest" : "r08/f08",
        "east" : "r07/f10",
        "north" : "r08/f09",
        "northeast" : "r08/f10",
        "west" : "r07/f08",
    ]));
    
}
