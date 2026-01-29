#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(49);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f25",
        "southwest" : "r07/f23",
        "south" : "r06/f24",
        "northwest" : "r08/f23",
        "east" : "r07/f25",
        "north" : "r08/f24",
        "northeast" : "r08/f25",
        "west" : "r07/f23",
    ]));
    
}
