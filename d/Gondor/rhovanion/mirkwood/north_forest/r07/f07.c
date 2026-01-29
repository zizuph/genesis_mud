#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(53);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f08",
        "southwest" : "r06/f06",
        "south" : "r06/f07",
        "northwest" : "r08/f06",
        "east" : "r07/f08",
        "north" : "r08/f07",
        "northeast" : "r08/f08",
        "west" : "r07/f06",
    ]));
    
}
