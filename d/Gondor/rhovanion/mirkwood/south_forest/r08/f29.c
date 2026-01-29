#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f30",
        "southwest" : "r09/f28",
        "south" : "r09/f29",
        "northwest" : "r07/f28",
        "east" : "r08/f30",
        "north" : "r07/f29",
        "northeast" : "r07/f30",
        "west" : "r08/f28",
    ]));
    
}
