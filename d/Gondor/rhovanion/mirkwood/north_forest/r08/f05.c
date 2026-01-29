#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(41);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r07/f06",
        "southwest" : "r07/f04",
        "south" : "r07/f05",
        "northwest" : "r09/f04",
        "east" : "r08/f06",
        "north" : "r09/f05",
        "northeast" : "r09/f06",
        "west" : "r08/f04",
    ]));
    
}
