#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(38);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r07/f05",
        "southwest" : "r07/f03",
        "south" : "r07/f04",
        "northwest" : "r09/f03",
        "east" : "r08/f05",
        "north" : "r09/f04",
        "northeast" : "r09/f05",
        "west" : "r08/f03",
    ]));
    
}
