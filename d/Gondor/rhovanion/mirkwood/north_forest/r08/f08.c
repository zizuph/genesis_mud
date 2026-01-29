#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(67);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r07/f09",
        "southwest" : "r07/f07",
        "south" : "r07/f08",
        "northwest" : "r09/f07",
        "east" : "r08/f09",
        "north" : "r09/f08",
        "northeast" : "r09/f09",
        "west" : "r08/f07",
    ]));
    
}
