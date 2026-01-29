#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f29",
        "southwest" : "r07/f27",
        "south" : "r07/f28",
        "northwest" : "r09/f27",
        "east" : "r08/f29",
        "north" : "r09/f28",
        "northeast" : "r09/f29",
        "west" : "r08/f27",
    ]));
    
}
