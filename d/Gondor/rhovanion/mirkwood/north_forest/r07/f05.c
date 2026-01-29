#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(41);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r06/f06",
        "southwest" : "r06/f04",
        "south" : "r06/f05",
        "northwest" : "r08/f04",
        "east" : "r07/f06",
        "north" : "r08/f05",
        "northeast" : "r08/f06",
        "west" : "r07/f04",
    ]));
    
}
