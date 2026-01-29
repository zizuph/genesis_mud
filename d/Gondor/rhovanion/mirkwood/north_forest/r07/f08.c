#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(34);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f09",
        "southwest" : "r06/f07",
        "south" : "r06/f08",
        "northwest" : "r08/f07",
        "east" : "r07/f09",
        "north" : "r08/f08",
        "northeast" : "r08/f09",
        "west" : "r07/f07",
    ]));
    
}
