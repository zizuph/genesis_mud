#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(35);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f27",
        "southwest" : "r06/f25",
        "south" : "r06/f26",
        "northwest" : "r08/f25",
        "east" : "r07/f27",
        "north" : "r08/f26",
        "northeast" : "r08/f27",
        "west" : "r07/f25",
    ]));
    
}
