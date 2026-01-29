#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(28);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f29",
        "southwest" : "r06/f27",
        "south" : "r06/f28",
        "northwest" : "r08/f27",
        "east" : "r07/f29",
        "north" : "r08/f28",
        "northeast" : "r08/f29",
        "west" : "r07/f27",
    ]));
    
}
