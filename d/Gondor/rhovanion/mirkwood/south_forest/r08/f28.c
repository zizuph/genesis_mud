#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f29",
        "southwest" : "r09/f27",
        "south" : "r09/f28",
        "northwest" : "r07/f27",
        "east" : "r08/f29",
        "north" : "r07/f28",
        "northeast" : "r07/f29",
        "west" : "r08/f27",
    ]));
    
}
